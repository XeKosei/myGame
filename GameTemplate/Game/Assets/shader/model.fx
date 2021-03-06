/*!
 * @brief	シンプルなモデルシェーダー。
 */


////////////////////////////////////////////////
// 定数バッファ。
////////////////////////////////////////////////
//モデル用の定数バッファ
cbuffer ModelCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
};

////////////////////////////////////////////////
// 構造体
////////////////////////////////////////////////
//スキニング用の頂点データをひとまとめ。
struct SSkinVSIn{
	int4  Indices  	: BLENDINDICES0;
    float4 Weights  : BLENDWEIGHT0;
};
//頂点シェーダーへの入力。
struct SVSIn{
	float4 pos 		: POSITION;		//モデルの頂点座標。
	float3 normal	: NORMAL;		//法線
	float2 uv 		: TEXCOORD0;	//UV座標。
	SSkinVSIn skinVert;				//スキン用のデータ。
};
//ピクセルシェーダーへの入力。
struct SPSIn{
	float4 pos 			: SV_POSITION;	//スクリーン空間でのピクセルの座標。
	float3 normal		: NORMAL;		//法線
	float2 uv 			: TEXCOORD0;	//uv座標。
	float3 worldPos		: TEXCOORD1;
	float3 normalInView : TEXCOORD2;
};

//ライト用の構造体たち
struct DirLigData
{
	float3 ligDir;		//ライトの方向
	float3 ligColor;	//ライトのカラー
};

struct PointLigData
{
	float3 ligPos;		//ライトの位置
	float3 ligColor;	//ライトのカラー
	float ligRange;		//ライトの影響範囲の半径
};

struct SpotLigData
{
	float3 ligPos;		//ライトの位置
	float3 ligColor;	//ライトのカラー
	float ligRange;		//ライトの影響範囲の半径
	float3 ligDir;		//ライトの射出方向
	float ligAngle;		//ライトの射出角度
};
struct SpotLigCameraData
{
	float4x4 mSpotLVP;
	float3 spotLightCameraPos;
	float spotLightCameraAngle;
	float3 spotLightCameraDir;
	float isSpotLightSwitchOn;
};
cbuffer LightDataCb : register(b1)
{
	//各配列数はCLightManager.hのMaxLightNumと同じにすること
	SpotLigCameraData spotLigCameraData[3];
	DirLigData directionLigData[5];
	PointLigData pointLigData[50];
	SpotLigData spotLigData[20];
	float3 eyePos;
	int directionLigNum;
	int pointLigNum;
	int spotLigNum;
};

////////////////////////////////////////////////
// グローバル変数。
////////////////////////////////////////////////
Texture2D<float4> g_albedo : register(t0);				//アルベドマップ
StructuredBuffer<float4x4> g_boneMatrix : register(t3);	//ボーン行列。
sampler g_sampler : register(s0);	//サンプラステート。

////////////////////////////////////////////////
// 関数定義。
////////////////////////////////////////////////
float3 CalcLambertDiffuse(float3 ligDir, float3 ligColor, float3 normal);
float3 CalcPhongSpecular(float3 ligDir, float3 ligColor, float3 worldPos, float3 normal);
float3 CalcLimLight(float3 ligDir, float3 ligColor, float3 normalInView, float3 normal);
float3 CalcDirectionLight(SPSIn psIn);
float3 CalcPointLight(SPSIn psIn);
float3 CalcSpotLight(SPSIn psIn);

/// <summary>
//スキン行列を計算する。
/// </summary>
float4x4 CalcSkinMatrix(SSkinVSIn skinVert)
{
	float4x4 skinning = 0;	
	float w = 0.0f;
	[unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += g_boneMatrix[skinVert.Indices[i]] * skinVert.Weights[i];
        w += skinVert.Weights[i];
    }
    
    skinning += g_boneMatrix[skinVert.Indices[3]] * (1.0f - w);
	
    return skinning;
}

/// <summary>
/// 頂点シェーダーのコア関数。
/// </summary>
SPSIn VSMainCore(SVSIn vsIn, uniform bool hasSkin)
{
	SPSIn psIn;
	float4x4 m;
	if( hasSkin ){
		m = CalcSkinMatrix(vsIn.skinVert);
	}else{
		m = mWorld;
	}
	psIn.pos = mul(m, vsIn.pos);

	psIn.worldPos = psIn.pos;

	psIn.pos = mul(mView, psIn.pos);
	psIn.pos = mul(mProj, psIn.pos);

	//法線を回転させる
	psIn.normal = mul(mWorld, vsIn.normal);

	psIn.normal = normalize(psIn.normal);

	psIn.normalInView = mul(mView, psIn.normal);

	psIn.uv = vsIn.uv;

	return psIn;
}

/// <summary>
/// スキンなしメッシュ用の頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSMain(SVSIn vsIn)
{
	return VSMainCore(vsIn, false);
}
/// <summary>
/// スキンありメッシュの頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSSkinMain( SVSIn vsIn ) 
{
	return VSMainCore(vsIn, true);
}
/// <summary>
/// ピクセルシェーダーのエントリー関数。
/// </summary>
float4 PSMain(SPSIn psIn) : SV_Target0
{
	float4 finalColor = {0.0f, 0.0f, 0.0f, 1.0f};
	
	//ディレクションライトを計算
	finalColor.xyz += CalcDirectionLight(psIn);

	//ポイントライトを計算
	finalColor.xyz += CalcPointLight(psIn);

	//スポットライトを計算
	finalColor.xyz += CalcSpotLight(psIn);

	//環境光
	float3 ambientLig = {0.3f, 0.3f, 0.3f};
	finalColor.xyz += ambientLig;

	//テクスチャカラーを乗算
	float4 albedoColor = g_albedo.Sample(g_sampler, psIn.uv);
	finalColor *= albedoColor;

	return finalColor;
}

///Lambert拡散反射光を計算する。
float3 CalcLambertDiffuse(float3 ligDir, float3 ligColor, float3 normal)
{
	//ピクセルの法線(の反対向き)とライトの方向の内積を計算
	float t = dot(normal * -1.0f, ligDir);

	//内積の結果が0以下なら0にする。
	if (t < 0.0f)
	{
		t = 0.0f;
	}

	//拡散反射光を計算。
	return ligColor * t;
}

///Phong鏡面反射を計算する。
float3 CalcPhongSpecular(float3 ligDir, float3 ligColor, float3 worldPos, float3 normal)
{
	//反射ベクトルを求める。
	float3 refVec = reflect(ligDir, normal);

	//光が当たったサーフェイスから視点へと伸びるベクトルを求める。
	float3 toEye = eyePos - worldPos;
	toEye = normalize(toEye);

	//鏡面反射の強さを内積を使って求める。
	float t = dot(refVec, toEye);
	//内積の結果が0以下なら0にする。
	if (t < 0.0f)
	{
		t = 0.0f;
	}

	//鏡面反射の強さを絞る。
	t = pow(t, 3.0f);

	//鏡面反射光を計算
	return ligColor * t;
}


//リムライトを計算する。
float3 CalcLimLight(float3 ligDir, float3 ligColor, float3 normalInView, float3 normal)
{
	//サーフェイスの法線と光の入射方向に依存するリムの強さを求める。
	float power1 = 1.0f - max(0.0f, dot(ligDir, normal));
	//サーフェイスの法線と視線の方向に依存するリム強さを求める。
	float power2 = 1.0f - max(0.0f, normalInView.z * -1.0f);
	//最終的なリムの強さ	
	float limPower = power1 * power2;
	//リムの強さを指数関数的にする。
	limPower = pow(limPower, 3.0f);

	return ligColor * limPower;
}

///ディレクションライトを計算する。
float3 CalcDirectionLight(SPSIn psIn)
{
	float3 dirLig = { 0.0f, 0.0f, 0.0f };
	for (int i = 0; i < createdDirLigTotal; i++)
	{
		//Lambert拡散反射光を計算
		float3 diffLig = CalcLambertDiffuse(dirLigData[i].ligDir, dirLigData[i].ligColor, psIn.normal);
		//Specular鏡面反射光を計算
		float3 specLig = CalcPhongSpecular(dirLigData[i].ligDir, dirLigData[i].ligColor, psIn.worldPos, psIn.normal);
		//リムライト
		float3 limLig = CalcLimLight(dirLigData[i].ligDir, dirLigData[i].ligColor, psIn.normalInView, psIn.normal);

		dirLig += diffLig;
		dirLig += specLig;
		dirLig += limLig;
	}

	return dirLig;
}

//ポイントライトを計算する。
float3 CalcPointLight(SPSIn psIn)
{
	float3 pointLig = { 0.0f, 0.0f, 0.0f };

	for (int i = 0; i < createdPointLigTotal; i++)
	{
		//サーフェイスに入射しているポイントライトの光の向きを計算する。
		float3 ligDir = psIn.worldPos - pointLigData[i].ligPos;
		ligDir = normalize(ligDir);

		//減衰なしのLambert拡散反射光を計算する。
		float3 diffLig = CalcLambertDiffuse(ligDir, pointLigData[i].ligColor, psIn.normal);
		//減衰なしのSpecular鏡面反射光を計算する。
		float3 specLig = CalcPhongSpecular(ligDir, pointLigData[i].ligColor, psIn.worldPos, psIn.normal);
		//リムライト
		float3 limLig = CalcLimLight(ligDir, pointLigData[i].ligColor, psIn.normalInView, psIn.normal);

		//ポイントライトとの距離を計算する。
		float3 dis = length(psIn.worldPos - pointLigData[i].ligPos);
		//影響率は距離に比例して小さくなっていく。
		float affect = 1.0f - 1.0f / pointLigData[i].ligRange * dis;
		//影響力がマイナスにならないようにする。
		if (affect < 0.0f)
		{
			affect = 0.0f;
		}

		//影響の仕方を指数関数的にする。
		affect = pow(affect, 5.0f);

		//拡散反射光と鏡面反射光に減衰率を乗算して影響を弱める。
		diffLig *= affect;
		specLig *= affect;
		limLig *= affect;

		pointLig += diffLig;
		pointLig += specLig;
		pointLig += limLig;
	}

	return pointLig;
}

float3 CalcSpotLight(SPSIn psIn)
{
	float3 spotLig = {0.0f, 0.0f, 0.0f};

	for (int i = 0; i < createdSpotLigTotal; i++)
	{
		//このサーフェイスに入射しているスポットライトの光の向きを計算
		float3 dirToSurface = psIn.worldPos - spotLigData[i].ligPos;
		dirToSurface = normalize(dirToSurface);

		//減衰なしのLambert拡散反射光を計算する。
		float3 diffLig = CalcLambertDiffuse(dirToSurface, spotLigData[i].ligColor, psIn.normal);
		//減衰なしのSpecular鏡面反射光を計算する。
		float3 specLig = CalcPhongSpecular(dirToSurface, spotLigData[i].ligColor, psIn.worldPos, psIn.normal);
		//リムライト
		float3 limLig = CalcLimLight(dirToSurface, spotLigData[i].ligColor, psIn.normalInView, psIn.normal);

		//距離による影響率を計算する。
		//スポットライトとの距離
		float3 dis = length(psIn.worldPos - spotLigData[i].ligPos);
		//影響率は距離に比例して小さくなっていく。
		float affect = 1.0f - 1.0f / spotLigData[i].ligRange * dis;
		//影響力がマイナスにならないようにする。
		if (affect < 0.0f) {
			affect = 0.0f;
		}
		//影響の仕方を指数関数的にする。
		affect = pow( affect, 3.0f);

		//拡散反射光と鏡面反射光に減衰率を乗算して影響を弱める。
		diffLig *= affect;
		specLig *= affect;
		limLig *= affect;

		//入射光と射出方向の角度を求める。
		//内積を求める。
		float angle = dot(dirToSurface, spotLigData[i].ligDir);
		//角度を求める。
		angle =  acos(angle);

		//角度による影響力を求める。
		affect = 1.0f - 1.0f / spotLigData[i].ligAngle * angle;
		//影響力がマイナスにならないようにする。
		if (affect < 0.0f) {
			affect = 0.0f;
		}
		//影響の仕方を指数関数的にする。
		affect = pow(affect, 0.5f);
		//角度による影響率を反射光に乗算して、影響を弱める。
		diffLig *= affect;
		specLig *= affect;
		limLig *= affect;

		spotLig += diffLig;
		spotLig += specLig;
		spotLig += limLig;
	}

	return spotLig;
}