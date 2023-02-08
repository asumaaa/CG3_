#pragma once

#include "DirectXMath.h"
#include "d3d12.h"
#include "d3dx12.h"
#include "vector"
#include "DirectionalLight.h"

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
public: // サブクラス
	// 定数バッファ用データ構造体 
	struct ConstBufferData
	{
		//環境光の色
		XMFLOAT3 ambientColor;
		float pad1;
		//平行光源用
		DirectionalLight::ConstBufferData dirLights[DirLightNum];
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

};

