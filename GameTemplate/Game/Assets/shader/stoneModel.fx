/*!
 * @brief	シンプルなモデルシェーダー。
 */

 //定数
static const float PI = 3.1415926f;         // π

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

	//頂点シェーダーの入力に接ベクトルと従ベクトルを追加
	float3 tangent : TANGENT;
	float3 biNormal : BINORMAL;
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
	float4 posInView	:TEXCOORD7;
	//ピクセルシェーダーの入力に接ベクトルと従ベクトルを追加
	float3 tangent  : TANGENT;      // 接ベクトル
	float3 biNormal : BINORMAL;     // 従ベクトル
};

////////////////////////////////////////////////
// グローバル変数。
////////////////////////////////////////////////
Texture2D<float4> g_albedo : register(t0);				//アルベドマップ
Texture2D<float4> g_normalMap : register(t1);			//法線マップ
Texture2D<float4> g_specularMap : register(t2);			//スペキュラマップ

Texture2D<float4> g_spotLightMap00 : register(t10);		//スポットライトマップ
Texture2D<float4> g_spotLightMap01 : register(t11);		//スポットライトマップ
Texture2D<float4> g_spotLightMap02 : register(t12);		//スポットライトマップ
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

	//接ベクトルと従ベクトルをワールド空間に変換する
	psIn.tangent = normalize(mul(mWorld, vsIn.tangent));
	psIn.biNormal = normalize(mul(mWorld, vsIn.biNormal));

	psIn.uv = vsIn.uv;

	//スポットライトビューのスクリーン空間の座標を計算
	psIn.posInSpotLVP00 = mul(spotLigCameraData[0].mSpotLVP, float4(psIn.worldPos, 1.0f));
	psIn.posInSpotLVP01 = mul(spotLigCameraData[1].mSpotLVP, float4(psIn.worldPos, 1.0f));
	psIn.posInSpotLVP02 = mul(spotLigCameraData[2].mSpotLVP, float4(psIn.worldPos, 1.0f));

	//セマンティクスが原因で、psIn.posはピクセルシェーダーにちゃんと値が渡されていないので、
	//代わりにpsIn.posInViewに値を代入。
	psIn.posInView = psIn.pos;

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

/// <summary>
/// フレネル反射を考慮した拡散反射を計算
/// </summary>
/// <remark>
/// この関数はフレネル反射を考慮した拡散反射率を計算します
/// フレネル反射は、光が物体の表面で反射する現象のとこで、鏡面反射の強さになります
/// 一方拡散反射は、光が物体の内部に入って、内部錯乱を起こして、拡散して反射してきた光のことです
/// つまりフレネル反射が弱いときには、拡散反射が大きくなり、フレネル反射が強いときは、拡散反射が小さくなります
///
/// </remark>
/// <param name="N">法線</param>
/// <param name="L">光源に向かうベクトル。光の方向と逆向きのベクトル。</param>
/// <param name="V">視線に向かうベクトル。</param>
/// <param name="roughness">粗さ。0～1の範囲。</param>
float CalcDiffuseFromFresnel(float3 N, float3 L, float3 V, float roughness)
{
	// ディズニーベースのフレネル反射による拡散反射を真面目に実装する。
	// 光源に向かうベクトルと視線に向かうベクトルのハーフベクトルを求める
	float3 H = normalize(L + V);

	float energyBias = lerp(0.0f, 0.5f, roughness);
	float energyFactor = lerp(1.0, 1.0 / 1.51, roughness);

	// 光源に向かうベクトルとハーフベクトルがどれだけ似ているかを内積で求める
	float dotLH = saturate(dot(L, H));

	// 光源に向かうベクトルとハーフベクトル、
	// 光が平行に入射したときの拡散反射量を求めている
	float Fd90 = energyBias + 2.0 * dotLH * dotLH * roughness;

	// 法線と光源に向かうベクトルwを利用して拡散反射率を求める
	float dotNL = saturate(dot(N, L));
	float FL = (1 + (Fd90 - 1) * pow(1 - dotNL, 5));

	// 法線と視点に向かうベクトルを利用して拡散反射率を求める
	float dotNV = saturate(dot(N, V));
	float FV = (1 + (Fd90 - 1) * pow(1 - dotNV, 5));

	// 法線と光源への方向に依存する拡散反射率と、法線と視点ベクトルに依存する拡散反射率を
	// 乗算して最終的な拡散反射率を求めている。PIで除算しているのは正規化を行うため
	return (FL * FV * energyFactor);
}

//ランバート拡散反射を計算する。
float3 CalcLambertDiffuse(float3 ligDir, float3 ligColor, float3 normal)
{
	float t = dot(normal, -ligDir);

	if (t < 0)
	{
		t = 0;
	}

	t /= PI;

	return ligColor * t;
}

// ベックマン分布を計算する
float Beckmann(float m, float t)
{
	float t2 = t * t;
	float t4 = t * t * t * t;
	float m2 = m * m;
	float D = 1.0f / (4.0f * m2 * t4);
	D *= exp((-1.0f / m2) * (1.0f - t2) / t2);
	return D;
}

// フレネルを計算。Schlick近似を使用
float SpcFresnel(float f0, float u)
{
	// from Schlick
	return f0 + (1 - f0) * pow(1 - u, 5);
}

/// Cook-Torranceモデルの鏡面反射を計算
float CookTorranceSpecular(float3 ligDir, float3 toEyeDir, float3 normal, float smooth)
{
	// マイクロファセットは粗さなので、
	// smoothから計算する。
	float microfacet = 1.0f - smooth;

	// 滑らかさを垂直入射の時のフレネル反射率として扱う
	// 滑らかさが高いほどフレネル反射は大きくなる
	float f0 = smooth;

	// ライトに向かうベクトルと視線に向かうベクトルのハーフベクトルを求める
	float3 H = normalize(ligDir + toEyeDir);

	// 各種ベクトルがどれくらい似ているかを内積を利用して求める
	float NdotH = max(0.001f, saturate(dot(normal, H)));
	float VdotH = max(0.001f, saturate(dot(toEyeDir, H)));
	float NdotL = max(0.001f, saturate(dot(normal, ligDir)));
	float NdotV = max(0.001f, saturate(dot(normal, toEyeDir)));

	// D項をベックマン分布を用いて計算する
	float D = Beckmann(microfacet, NdotH);

	// F項をSchlick近似を用いて計算する
	float F = SpcFresnel(f0, VdotH);

	// G項を求める
	float G = min(1.0f, min(2 * NdotH * NdotV / VdotH, 2 * NdotH * NdotL / VdotH));

	// m項を求める
	float m = PI * NdotV * NdotH;

	// ここまで求めた、値を利用して、Cook-Torranceモデルの鏡面反射を求める
	return max(F * D * G / m, 0.0);
}

float3 CalcLimLight(float3 ligDir, float3 ligColor, float3 normalInView, float3 normal)
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
	float maxColor = 0.5f;
	float minColor = 0.2f;

	if (albedoColor.x > maxColor)
		albedoColor.x = maxColor;
	else if (albedoColor.x < minColor);
		albedoColor.x = minColor;

	if (albedoColor.y > maxColor)
		albedoColor.y = maxColor;
	else if (albedoColor.y < minColor);
		albedoColor.y = minColor;

	if (albedoColor.z > maxColor)
		albedoColor.z = maxColor;
	else if (albedoColor.z < minColor);
		albedoColor.z = minColor;

	//albedoColor.w = 1.0f;

	//albedoColor = g_albedo.Sample(g_sampler, psIn.uv);

	float4 finalColor = 0.0f;
	finalColor.a = 1.0f;

	float3 specColor = albedoColor;
	//return float4(specColor, 1.0f);
	///////////法線マップ
	float3 normal = psIn.normal;
	//法線マップからタンジェントスペースの法線をサンプリングする
	float3 localNormal = g_normalMap.Sample(g_sampler, psIn.uv).xyz;

	// タンジェントスペースの法線を0～1の範囲から-1～1の範囲に復元する
	localNormal = (localNormal - 0.5f) * 2.0f;
	//タンジェントスペースの法線をワールドスペースに変換する
	normal = normalize(psIn.tangent * localNormal.x + psIn.biNormal * localNormal.y + normal * localNormal.z);


	///////////スペキュラマップ
	//スペキュラマップからスペキュラ反射の強さをサンプリング
	float smooth = 0.5f; //g_specularMap.Sample(g_sampler, psIn.uv).r;

	float metallic = 0.01f;//g_specularMap.Sample(g_sampler, psIn.uv).g;

	// 視線に向かって伸びるベクトルを計算する
	float3 toEye = normalize(eyePos - psIn.worldPos);

	//ディレクションライト
	for (int i = 0;i < directionLigNum;i++)
	{
		// フレネル反射を考慮した拡散反射を計算
		float diffuseFromFresnel = CalcDiffuseFromFresnel(normal, -directionLigData[i].ligDir, toEye, 1.0f - smooth);

		// 最終的な拡散反射光を計算する
		float3 diffuseLig = albedoColor * diffuseFromFresnel * directionLigData[i].ligColor / PI;

		//フォン鏡面反射
		float3 specularLig = CookTorranceSpecular(
			-directionLigData[i].ligDir, toEye, normal, smooth)
			* directionLigData[i].ligColor;

		specularLig *= lerp(float3(1.0f, 1.0f, 1.0f), specColor, metallic);

		//リムライト
		//float3 limLig = CalcLimLight(spotLigDir, spotLigData[i].ligColor, psIn.normalInView,normal);

		float3 finalLig = diffuseLig * (1.0 - smooth) + specularLig;

		finalColor.xyz += finalLig;
	}

	//ポイントライト
	for (int i = 0; i < pointLigNum; i++)
	{
		float3 pointLigDir = psIn.worldPos - pointLigData[i].ligPos;
		pointLigDir = normalize(pointLigDir);

		// フレネル反射を考慮した拡散反射を計算
		float diffuseFromFresnel = CalcDiffuseFromFresnel(normal, -pointLigDir, toEye, 1.0f - smooth);

		//ランバート拡散反射
		float3 lambertDiffuse = CalcLambertDiffuse(pointLigDir, pointLigData[i].ligColor, normal);

		// 最終的な拡散反射光を計算する
		float3 diffuseLig = albedoColor * diffuseFromFresnel * pointLigData[i].ligColor / PI;

		//フォン鏡面反射
		float3 specularLig = CookTorranceSpecular(
			-pointLigDir, toEye, normal, smooth)
			* pointLigData[i].ligColor;

		specularLig *= lerp(float3(1.0f, 1.0f, 1.0f), specColor, metallic);

		//リムライト
		//float3 limLig = CalcLimLight(spotLigDir, spotLigData[i].ligColor, psIn.normalInView,normal);

		float3 finalLig = diffuseLig * (1.0 - smooth) + specularLig;

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

			if (zInSpotLVP < zInSpotLightMap + 0.0001f)//&& zInSpotLVP <= 1.0f)
			{
				////透視の処理
				//if (i == 0)	//懐中電灯のスポットライトのときのみ
				//{
				//	float2 uv = psIn.posInView.xy / psIn.posInView.w;
				//	uv *= float2(0.5f, -0.5f);
				//	uv += 0.5f;

				//	float4 clairvoyanceMap = g_clairvoyanceMap.Sample(g_sampler, uv);

				//	if (clairvoyanceMap.x > 0.0f)
				//	{
				//		albedoColor.x = zInSpotLightMap * 10.0f;
				//		albedoColor.y = 0.0f;
				//		albedoColor.z = 0.0f;
				//	}
				//}
				////ここまで透視処理

				float3 spotLigDir = psIn.worldPos - spotLigData[i].ligPos;
				spotLigDir = normalize(spotLigDir);

				// フレネル反射を考慮した拡散反射を計算
				float diffuseFromFresnel = CalcDiffuseFromFresnel(normal, -spotLigDir, toEye, 1.0f - smooth);

				//ランバート拡散反射
				float3 lambertDiffuse = CalcLambertDiffuse(spotLigDir, spotLigData[i].ligColor, normal);


				// 最終的な拡散反射光を計算する
				float3 diffuseLig = albedoColor * diffuseFromFresnel * spotLigData[i].ligColor / PI;

				//フォン鏡面反射
				float3 specularLig = CookTorranceSpecular(
					-spotLigDir, toEye, normal, smooth)
					* spotLigData[i].ligColor;

				specularLig *= lerp(float3(1.0f, 1.0f, 1.0f), specColor, metallic);

				//リムライト
				//float3 limLig = CalcLimLight(spotLigDir, spotLigData[i].ligColor, psIn.normalInView,normal);

				float3 finalLig = diffuseLig * (1.0 - smooth) + specularLig;

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
				//return finalColor;
			}
		}
	}

	//環境光
	//懐中電灯に照らされていない場合は、遠くが暗く見えるようにする。
	//float3 ambientLig = 0.3f;
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

	finalColor.xyz += albedoColor * ambientLig * 0.8f;


	return finalColor;
}
