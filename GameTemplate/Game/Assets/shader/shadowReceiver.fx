/*!
 * @brief	シンプルなモデルシェーダー。
 */


 ////////////////////////////////////////////////
 // 定数バッファ。
 ////////////////////////////////////////////////
 //モデル用の定数バッファ
cbuffer ModelCb : register(b0) {
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
};

//ライト用の構造体たち
struct DirectionLigData
{
	float3 ligDir;
	float3 ligColor;
};

struct PointLigData
{
	float3 ligPos;
	float3 ligColor;
	float ligRange;
};

struct SpotLigData
{
	float3 ligPos;
	float3 ligColor;
	float ligRange;
	float3 ligDir;
	float ligAngle;
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
	DirectionLigData directionLigData[5];
	PointLigData pointLigData[50];
	SpotLigData spotLigData[20];
	float3 eyePos;
	int directionLigNum;
	int pointLigNum;
	int spotLigNum;
};

cbuffer LightCameraCb : register(b2)
{
	float4x4 mLVP;
	float3 lightCameraPos;
	float3 lightCameraDir;
};

////////////////////////////////////////////////
// 構造体
////////////////////////////////////////////////
//スキニング用の頂点データをひとまとめ。
struct SSkinVSIn {
	int4  Indices  	: BLENDINDICES0;
	float4 Weights  : BLENDWEIGHT0;
};
//頂点シェーダーへの入力。
struct SVSIn {
	float4 pos 		: POSITION;		//モデルの頂点座標。
	float3 normal	: NORMAL;		//法線
	float2 uv 		: TEXCOORD0;	//UV座標。
	SSkinVSIn skinVert;				//スキン用のデータ。
};
//ピクセルシェーダーへの入力。
struct SPSIn {
	float4 pos 			: SV_POSITION;	//スクリーン空間でのピクセルの座標。
	float3 normal		: NORMAL;		//法線
	float2 uv 			: TEXCOORD0;	//uv座標。
	float3 worldPos		: TEXCOORD1;
	float3 normalInView : TEXCOORD2;
	float4 posInLVP 	: TEXCOORD3;
	float4 posInSpotLVP00 : TEXCOORD4;
	float4 posInSpotLVP01 : TEXCOORD5;
	float4 posInSpotLVP02 : TEXCOORD6;
};

////////////////////////////////////////////////
// グローバル変数。
////////////////////////////////////////////////
Texture2D<float4> g_albedo : register(t0);				//アルベドマップ
Texture2D<float4> g_shadowMap : register(t10);			//シャドウマップ
Texture2D<float4> g_clairvoyanceMap : register(t11);	//透視マップ
Texture2D<float4> g_spotLightMap00 : register(t12);		//スポットライトマップ
Texture2D<float4> g_spotLightMap01 : register(t13);		//スポットライトマップ
Texture2D<float4> g_spotLightMap02 : register(t14);		//スポットライトマップ
StructuredBuffer<float4x4> g_boneMatrix : register(t3);	//ボーン行列。
sampler g_sampler : register(s0);	//サンプラステート。

////////////////////////////////////////////////
// 関数定義。
////////////////////////////////////////////////

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
	if (hasSkin) {
		m = CalcSkinMatrix(vsIn.skinVert);
	}
	else {
		m = mWorld;
	}
	psIn.pos = mul(m, vsIn.pos);
	
	psIn.worldPos = psIn.pos;

	psIn.pos = mul(mView, psIn.pos);
	psIn.pos = mul(mProj, psIn.pos);
	psIn.normal = mul(m, vsIn.normal);
	psIn.normal = normalize(psIn.normal);

	psIn.normalInView = mul(mView, psIn.normal);

	psIn.uv = vsIn.uv;

	psIn.posInLVP = mul(mLVP,float4(psIn.worldPos, 1.0f));

	////本来の比較用の距離はこっち
	//psIn.posInLVP.z = length(psIn.worldPos - lightCameraPos) / 1000.0f;
	//ここから平行光源の深度チェックのテスト用。
	//ライトの向きを取得。
	float3 cameraDir = lightCameraDir;
	//正規化されてるはずだけど、念の為。
	cameraDir = normalize(cameraDir);
	float3 axisX = {1.0f,0.0f,0.0f};
	float3 lightCameraAnotherAxis = cross(axisX,cameraDir);
	//axisX,lightCameraAnotherAxisで構成される平面にpsIn.worldPosから垂線をおろす。
	float3 start = psIn.worldPos;
	//スタート地点からカメラの向きをプラスして仮想の垂線をつくる。
	float3 end = psIn.worldPos + -100 * cameraDir;
	//ポリゴンと線分の交差判定を参考に、
	//仮想の垂線とlightCameraPos,lightCameraPos+axisX,lightCameraPos+lightCameraAnotherAxisの
	//3点でできる平面との交点を求めていく。
	float3 toStart = start - lightCameraPos;
	float3 toEnd = end - lightCameraPos;
	float a = dot(cameraDir,toStart);
	float3 cameraDirRev = -cameraDir;
	float b = dot(cameraDirRev,toEnd);
	//crosspointは交点 = 3点でできる平面と垂線の交点。depthの開始点になる。
	float3 crossPoint = toStart - toEnd;
	crossPoint *= b / (a+b);
	crossPoint += end;

	psIn.posInLVP.z = length(psIn.worldPos - crossPoint)/2000.0f;
	//ここまで平行光源の深度チェックのテスト用。

	//スポットライトビューのスクリーン空間の座標を計算
	psIn.posInSpotLVP00 = mul(spotLigCameraData[0].mSpotLVP, float4(psIn.worldPos, 1.0f));
	psIn.posInSpotLVP01 = mul(spotLigCameraData[1].mSpotLVP, float4(psIn.worldPos, 1.0f));
	psIn.posInSpotLVP02 = mul(spotLigCameraData[2].mSpotLVP, float4(psIn.worldPos, 1.0f));

	////ライトの向きを取得。
	//cameraDir = spotLightCameraDir;
	////正規化されてるはずだけど、念の為。
	//cameraDir = normalize(cameraDir);
	//lightCameraAnotherAxis = cross(axisX, cameraDir);
	////axisX,lightCameraAnotherAxisで構成される平面にpsIn.worldPosから垂線をおろす。
	//start = psIn.worldPos;
	////スタート地点からカメラの向きをプラスして仮想の垂線をつくる。
	//end = psIn.worldPos + -100 * cameraDir;
	////ポリゴンと線分の交差判定を参考に、
	////仮想の垂線とlightCameraPos,lightCameraPos+axisX,lightCameraPos+lightCameraAnotherAxisの
	////3点でできる平面との交点を求めていく。
	//toStart = start - spotLightCameraPos;
	//toEnd = end - spotLightCameraPos;
	//a = dot(cameraDir, toStart);
	//cameraDirRev = -cameraDir;
	//b = dot(cameraDirRev, toEnd);
	////crosspointは交点 = 3点でできる平面と垂線の交点。depthの開始点になる。
	//crossPoint = toStart - toEnd;
	//crossPoint *= b / (a + b);
	//crossPoint += end;

	//psIn.posInSpotLVP.z = length(psIn.worldPos - crossPoint) / 2000.0f;

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
SPSIn VSSkinMain(SVSIn vsIn)
{
	return VSMainCore(vsIn, true);
}

//ランバート拡散反射を計算する。
float3 CalcLambertDiffuse(float3 ligDir, float3 ligColor,float3 normal )
{
	float t = dot(normal, -ligDir);
	
	if (t < 0)
	{
		t = 0;
	}

	t /= 3.1415926;

	return ligColor * t;
}

//フォン鏡面反射を計算する。
float3 CalcPhongSpecular(float3 ligDir, float3 ligColor, float3 worldPos, float3 normal)
{
	float3 toEye = eyePos - worldPos;
	toEye = normalize(toEye);

	float3 refVec = reflect(ligDir, normal);

	float t = dot(toEye, refVec);
	
	if (t < 0)
	{
		t = 0;
	}

	t = pow(t, 5.0f);

	return ligColor * t;
}

float3 CalcLimLight(float3 ligDir, float3 ligColor, float3 normalInView,float3 normal)
{
	float power1 = 1.0f - max(0.0f, dot(ligDir, normal));

	float power2 = 1.0f - max(0.0f, normalInView.z * -1.0f);

	float limPower = power1 * power2;

	limPower = pow(limPower, 5.0f);

	return ligColor * limPower;
}

/// <summary>
/// ピクセルシェーダーのエントリー関数。
/// </summary>
float4 PSMain(SPSIn psIn) : SV_Target0
{
	float4 albedoColor = g_albedo.Sample(g_sampler, psIn.uv);

	float4 finalColor = 0.0f;
	finalColor.a = 1.0f;


	//ディレクションライト
	for (int i = 0;i < directionLigNum;i++)
	{
		//ランバート拡散反射
		float3 diffuseLig = CalcLambertDiffuse(directionLigData[i].ligDir, directionLigData[i].ligColor,psIn.normal);

		//フォン鏡面反射
		float3 specularLig = CalcPhongSpecular(directionLigData[i].ligDir, directionLigData[i].ligColor, psIn.worldPos, psIn.normal);

		//リムライト
		//float3 limLig = CalcLimLight(directionLigData[i].ligDir, directionLigData[i].ligColor, psIn.normalInView, psIn.normal);

		float3 finalLig = diffuseLig + specularLig;

		finalColor.xyz +=  finalLig;
	}

	//ポイントライト
	for (int i = 0; i < pointLigNum; i++)
	{
		float3 pointLigDir = psIn.worldPos - pointLigData[i].ligPos;
		pointLigDir = normalize(pointLigDir);

		//ランバート拡散反射
		float3 diffuseLig = CalcLambertDiffuse(pointLigDir, pointLigData[i].ligColor, psIn.normal);

		//フォン鏡面反射
		float3 specularLig = CalcPhongSpecular(pointLigDir,pointLigData[i].ligColor,psIn.worldPos,psIn.normal);

		//リムライト
		//float3 limLig = CalcLimLight(pointLigDir, pointLigData[i].ligColor, psIn.normalInView, psIn.normal);

		float3 finalLig = diffuseLig +specularLig;

		//距離による減衰

		float3 distance = length(psIn.worldPos - pointLigData[i].ligPos);

		float affect = 1.0f - 1.0f / pointLigData[i].ligRange * distance;

		if (affect < 0)
			affect = 0;

		affect = pow(affect, 3.0f);

		finalLig *= affect;

		finalColor.xyz += finalLig;
	}
	Texture2D<float4> spotLightMap[3];
	spotLightMap[0] = g_spotLightMap00;
	spotLightMap[1] = g_spotLightMap01;
	spotLightMap[2] = g_spotLightMap02;

	float4 posInSpotLVP[3];
	posInSpotLVP[0] = psIn.posInSpotLVP00;
	posInSpotLVP[1] = psIn.posInSpotLVP01;
	posInSpotLVP[2] = psIn.posInSpotLVP02;

	//スポットライト
	for (int i = 0; i < spotLigNum; i++)
	{
		float2 spotLightMapUV = posInSpotLVP[i].xy / posInSpotLVP[i].w;
		spotLightMapUV *= float2(0.5f, -0.5f);
		spotLightMapUV += 0.5f;

		float zInSpotLVP = posInSpotLVP[i].z / posInSpotLVP[i].w;
		if (spotLightMapUV.x > 0.0f && spotLightMapUV.x < 1.0f
			&& spotLightMapUV.y > 0.0f && spotLightMapUV.y < 1.0f)
		{
			float zInSpotLightMap = spotLightMap[i].Sample(g_sampler, spotLightMapUV).x;

			if (zInSpotLVP < zInSpotLightMap + 0.0001f)// && zInSpotLVP <= 1.0f)
			{
				//透視の処理
				float4 clairvoyanceMap = g_clairvoyanceMap.Sample(g_sampler, spotLightMapUV);
				if (clairvoyanceMap.x > 0.0f)
				{	
					albedoColor.x = zInSpotLightMap * 10.0f;
					albedoColor.y = 0.0f;
					albedoColor.z = 0.0f;		
				}
				//ここまで透視処理

				float3 spotLigDir = psIn.worldPos - spotLigData[i].ligPos;
				spotLigDir = normalize(spotLigDir);

				//ランバート拡散反射
				float3 diffuseLig = CalcLambertDiffuse(spotLigDir, spotLigData[i].ligColor, psIn.normal);

				//フォン鏡面反射
				float3 specularLig = CalcPhongSpecular(spotLigDir, spotLigData[i].ligColor, psIn.worldPos, psIn.normal);

				//リムライト
				//float3 limLig = CalcLimLight(spotLigDir, spotLigData[i].ligColor, psIn.normalInView, psIn.normal);

				float3 finalLig = diffuseLig + specularLig;

				//距離による減衰

				float3 distance = length(psIn.worldPos - spotLigData[i].ligPos);

				float affect = 1.0f - 1.0f / spotLigData[i].ligRange * distance;

				if (affect < 0)
					affect = 0;

				affect = pow(affect, 3.0f);

				finalLig *= affect;

				//角度による減衰
				float3 toGround = psIn.worldPos - spotLigData[i].ligPos;
				toGround = normalize(toGround);

				float angle = dot(toGround, spotLigData[i].ligDir);

				//floatの誤差かacos(1)が0に、acos(-1)がπになるはずなのにNanになっていたので臨時変更(錦織)
				if (-1 < angle && angle < 1)
				{
					angle = acos(angle);
				}
				else if (angle > 0.9)
				{
					angle = 0;
				}
				else
				{
					angle = acos(-1.0f);
				}

				affect = 1.0f - 1.0f / spotLigData[i].ligAngle * angle;
				if (affect <= 0.0f)
				{
					affect = 0.0f;
				}
				else
				{
					//0より大きい時だけ乗算
					affect = pow(affect, 0.5f);
				}

				finalLig *= affect;

				finalColor.xyz += finalLig;
			}
		}
	}

	//環境光
	//懐中電灯に照らされていない場合は、遠くが暗く見えるようにする。
	float3 ambientLig = 1 - (length(eyePos - psIn.worldPos) * 0.001f);
	for (int i = 0; i < spotLigNum; i++)
	{
		if (spotLigCameraData[i].isSpotLightSwitchOn == 1)
		{
			float3 toPsInDir = psIn.worldPos - spotLigCameraData[i].spotLightCameraPos;
			toPsInDir = normalize(toPsInDir);
			float3 spotLigDir = normalize(spotLigCameraData[i].spotLightCameraDir);
			float toPsInAngle = dot(toPsInDir, spotLigDir);
			toPsInAngle = acos(toPsInAngle);
			if (toPsInAngle < 0.0f)
			{
				toPsInAngle *= -1.0f;
			}
			float spotLigAngle = spotLigCameraData[i].spotLightCameraAngle;
			spotLigAngle /= 2;

			if (toPsInAngle <= spotLigAngle && ambientLig.r <= 0.3f)
			{
				ambientLig = 0.3f;
			}
		}
	}

	finalColor.xyz += ambientLig;
	
	finalColor *= albedoColor;

	//影
	float2 shadowMapUV = psIn.posInLVP.xy / psIn.posInLVP.w;
	shadowMapUV *= float2(0.5f, -0.5f);
	shadowMapUV += 0.5f;

	//float zInLVP = psIn.posInLVP.z;
	float zInLVP = psIn.posInLVP.z / psIn.posInLVP.w;

	if( shadowMapUV.x > 0.0f && shadowMapUV.x < 1.0f && shadowMapUV.y > 0.0f && shadowMapUV.y < 1.0f)
	{
		//シャドウマップからライトからの距離、距離の2乗をサンプリング
		float2 shadowValue = g_shadowMap.Sample(g_sampler,shadowMapUV).xy;
		
		//まずこのピクセルが遮蔽されているか調べる
		//zInLVPはライトから影が描かれるモデルへの距離、shadowValue.rはライトから影を落とすモデルへの距離
		//影が描かれるモデルへの距離より影を落とすモデルへの距離が短いなら影が描かれるモデルは遮蔽されている。
		if(zInLVP > shadowValue.r && zInLVP <= 1.0f)// && zInLVP < shadowValue.r + 0.1f)
		{
			//チェビシェフの不等式を使う
			float depth_sq = shadowValue.x * shadowValue.x;
			//このグループの分散具合を求める
			//分散が大きいほど、varianceの値は大きくなる。
			float variance = min(max(shadowValue.y - depth_sq,0.0001f),1.0f);
			//このピクセルのライトから見た深度値とシャドウマップの平均の深度値の差を求める。
			float md = zInLVP - shadowValue.x;
			//光が届く確率を求める
			float lit_factor = variance / (variance + md * md);
			//影の色を求める
			float3 shadowColor = finalColor.xyz * 0.3f;
			
			//光が当たる確率を使って通常カラーとシャドウカラーを線形補間
			finalColor.xyz = lerp(shadowColor,finalColor.xyz,lit_factor);
		}

		/*
		float zInShadowMap = g_shadowMap.Sample(g_sampler, shadowMapUV).r;
		if (zInLVP > zInShadowMap) {
			finalColor.xyz *= 0.5f;
		}*/
	}

	return finalColor;
}
