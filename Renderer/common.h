#pragma once

#include <wrl/client.h>

#include <dxgi1_6.h>
#include <d3d12.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d12.lib")

#include <stdint.h>
#include <string>
#include <assert.h>

#define RELEASE(res) res->Release(); res = NULL;
#define FRAMEBUFFERS_COUNT 3
