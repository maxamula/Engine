#pragma once

#include <wrl/client.h>

#include <dxgi1_6.h>
#include <d3d12.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d12.lib")

#include <stdint.h>
#include <string>
#include <assert.h>
#include <wrl/client.h>

using namespace Microsoft::WRL;

#define MOVE(a) a; a = {}; 

#define RELEASE(res) if(res){res->Release(); res = NULL;}
#define FRAMEBUFFERS_COUNT 3
