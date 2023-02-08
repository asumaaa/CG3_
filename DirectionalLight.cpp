#include "DirectionalLight.h"

using namespace DirectX;

/// <summary>
/// 静的メンバ変数の実体
/// </summary>
ID3D12Device* DirectionalLight::device = nullptr;

void DirectionalLight::StaticInitialize(ID3D12Device* device)
{
	//再初期化チェック 
	assert(!DirectionalLight::device); 
	//nullptrチェック 
	assert(device);
	// 静的メンバ変数のセット 
	DirectionalLight::device = device;
}

DirectionalLight* DirectionalLight::Create()
{
	//3Dオブジェクトのインスタンスを生成 
	DirectionalLight* instance = new DirectionalLight();
	//初期化
	instance->Initialize();
	//生成したインスタンスを返す
	return instance;

}

void DirectionalLight::TransferConstBuffer()
{
	HRESULT result;
	// 定数バッファヘデータ転送
	ConstBufferData* constMap = nullptr;
	result = constBuff->Map(0, nullptr, (void**)&constMap); 
	if (SUCCEEDED(result)) 
	{
		constMap->lightv = -lightdir;
		constMap->lightcolor = lightcolor; 
		constBuff->Unmap(0, nullptr);
	}
}

void DirectionalLight::SetLightDir(const XMVECTOR& lightdir)
{
	// 正規化してセット
	this->lightdir = XMVector3Normalize(lightdir);
	dirty = true;
}

void DirectionalLight::SetLightColor(const XMFLOAT3& lightcolor)
{
	this->lightcolor = lightcolor;
	dirty = true;

}

void DirectionalLight::Initialize()
{
	HRESULT result;

	//定数バッファの生成
	CD3DX12_HEAP_PROPERTIES v1 = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	CD3DX12_RESOURCE_DESC v2 = CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff);
	result = device->CreateCommittedResource(
		&v1,
		D3D12_HEAP_FLAG_NONE,
		&v2,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuff)
	);

	//定数バッファへデータ転送
	TransferConstBuffer();
}

void DirectionalLight::Update()
{
	// 値の更新があった時だけ定数バッファに転送する
	if (dirty) {
		TransferConstBuffer();
		dirty = false;
	}

}

void DirectionalLight::Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex)
{
	//定数バッファビューをセット
	cmdList->SetGraphicsRootConstantBufferView(rootParameterIndex, constBuff->GetGPUVirtualAddress());
}
