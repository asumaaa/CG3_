#pragma once

#include "DirectXMath.h"
#include "d3d12.h"
#include "d3dx12.h"
#include "vector"

class DirectionalLight
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

public: // サブクラス
	// 定数バッファ用データ構造体 
	struct ConstBufferData
	{
		XMVECTOR lightv;// ライトへの方向を表すベクトル
		XMFLOAT3 lightcolor; // ライトの色
		unsigned int active;
	};

private: // 静的メンバ変数 //デバイス
	static ID3D12Device* device;

public:
	// 静的メンバ関数 
	/// <summary> 
	/// /// 静的初期化
	/// </summary>
	/// <param name="device">1</param> 	
	static void StaticInitialize(ID3D12Device* device);

	/// <summary>
	///インスタンス生成
	/// </summary>
	/// <returns>インスタンス </returns> 
	static DirectionalLight* Create();


	/// <summary> 
	/// /// 定数バッファ転送
	/// </summary>
	void TransferConstBuffer();

	/// <summary>
	/// ライト方向をセット
	/// </summary>
	/// <paramname = "lightdir" >ライト方向< / param>
	void SetLightDir(const XMVECTOR & lightdir);

	/// <summary>
	/// ライト方向を取得
	/// </summary>
	/// <paramname = "lightdir" >ライト方向< / param>
	XMVECTOR GetLightDir() { return lightdir; }

	/// <summary> 
	/// ライト色をセット
	/// </summary>
	/// <paramname = "lightcolor" >ライト色< / param>
	void SetLightColor(const XMFLOAT3 & lightcolor);

	/// <summary> 
	/// ライト色を取得
	/// </summary>
	/// <paramname = "lightcolor" >ライト色< / param>
	XMFLOAT3 GetLightColor() { return lightcolor; }

	/// <summary> 
	/// 有効フラグをセット
	/// </summary>
	inline void SetActive(bool active) { this->active = active; }

	/// <summary> 
	/// 有効チェック
	/// </summary>
	inline bool IsActive() { return active; };


	void Initialize();
	void Update();
	void Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex);

private: // メンバ変数
	// 定数バッファ
	ComPtr<ID3D12Resource> constBuff;
	//ライト光線方向(単位ベクトル) 
	XMVECTOR lightdir = { 1,0,0,0 };
	// ライト色
	XMFLOAT3 lightcolor = { 1,1,1 };
	//ダーティフラグ
	bool dirty = false;
	//有効フラグ
	bool active = false;
};