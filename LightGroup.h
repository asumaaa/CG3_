#pragma once

#include "DirectXMath.h"
#include "d3d12.h"
#include "d3dx12.h"
#include "vector"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "CircleShadow.h"

class LightGroup
{
private: // エイリアス 
// Microsoft::WRLを省略
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public: // 定数
	static const int DirLightNum = 3;
	static const int PointLightNum = 3;
	static const int SpotLightNum = 3;
	static const int CircleShadowNum = 1;

public: // サブクラス
	// 定数バッファ用データ構造体 
	struct ConstBufferData
	{
		//環境光の色
		XMFLOAT3 ambientColor;
		float pad1;
		//平行光源用
		DirectionalLight::ConstBufferData dirLights[DirLightNum];
		//点光源用
		PointLight::ConstBufferData pointLights[PointLightNum];
		//スポットライト
		SpotLight::ConstBufferData spotLights[SpotLightNum];
		//丸影用
		CircleShadow::ConstBufferData circleShadows[CircleShadowNum];
	};

private:	//静的メンバ変数
	//デバイス
	static ID3D12Device* device;

public: // 静的メンバ関数 

	//静的初期化
	static void StaticInitialize(ID3D12Device* device);
	//インスタンス取得
	static LightGroup* Create();

public:	//メンバ関数

	// 定数バッファ転送
	void TransferConstBuffer();
	//環境光のライトをセット
	void SetAmbientColor(const XMFLOAT3& color);
	//平行光線の有効フラグをセット
	void SetDirLightActive(int index, bool active);
	//平行高原のライト方向をセット
	void SetDirLightDir(int index, const XMVECTOR& lightdir);
	//平行光源のライト色をセット
	void SetDirLightColor(int index, const XMFLOAT3& lightcolor);
	//標準のライト設定
	void DefaultLightSetting();

	//点光線の有効フラグをセット
	void SetPointLightActive(int index, bool active);
	//点高原のライト座標をセット
	void SetPointLightPos(int index, const XMFLOAT3& lightpos);
	//点光源のライト色をセット
	void SetPointLightColor(int index, const XMFLOAT3& lightcolor);
	//点光源のライト距離減衰係数をセット
	void SetPointLightAtten(int index, const XMFLOAT3& lightAtten);

	//スポットライトの有効フラグをセット
	void SetSpotLightActive(int index, bool active);
	//スポットライトのライト方向をセット
	void SetSpotLightDir(int index, const XMVECTOR& lightdir);
	//スポットライトのライト座標をセット
	void SetSpotLightPos(int index, const XMFLOAT3& lightpos);
	//スポットライトのライト色をセット
	void SetSpotLightColor(int index, const XMFLOAT3& lightcolor);
	//スポットライトのライト減衰係数をセット
	void SetSpotLightAtten(int index, const XMFLOAT3& lightAtten);
	//スポットライトのライト減衰角度をセット
	void SetSpotLightFactorAngle(int index, const XMFLOAT2& lightFactorAngle);

	//丸影の有効フラグセット
	void SetCircleShadowActive(int index, bool active);
	//丸影のキャスター座標セット
	void SetCircleShadowCasterPos(int index, const XMFLOAT3& casterPos); 
	//丸影の方向セット
	void SetCircleShadowDir(int index, const XMVECTOR& lightdir);
	//丸影のキャスターとライトの距離セット
	void SetCircleShadowDistanceCasterLight(int index, float distanceCasterLight); 
	//丸影の減衰係数セット
	void SetCircleShadowAtten(int index, const XMFLOAT3& lightAtten);
	//丸影の減衰角度セット
	void SetCircleShadowFactorAngle(int index, const XMFLOAT2& lightFactorAngle);


	void Initialize();
	void Update();
	void Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex);

private: // メンバ変数 
	// 定数バッファ
	ComPtr<ID3D12Resource> constBuff; 
	// 環境光の色
	XMFLOAT3 ambientColor = { 1,1,1 };
	// 平行光源の配列
	DirectionalLight dirLights[DirLightNum];
	//ダーティフラグ
	bool dirty = false;
	//点高原の配列
	PointLight pointLights[PointLightNum];
	//スポットライトの配列
	SpotLight spotLights[SpotLightNum];
	//丸影の配列
	CircleShadow circleShadows[CircleShadowNum];
};

