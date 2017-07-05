#include <Veritas/Definitions/Definitions.h>
#ifdef ANDROID
#include "File.h"
#include <cstdio>

using namespace Silexars::System::IO::FileSystem;

#include <android/asset_manager.h>
#include <android/log.h>

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__)

AAssetManager *assetManager;

static int asset_read(void* cookie, char* buf, int size) { return AAsset_read((AAsset*)cookie, buf, size); }
static int asset_write(void* cookie, const char* buf, int size) { return 0; }
static fpos_t asset_seek(void* cookie, fpos_t offset, int whence) { return AAsset_seek((AAsset*)cookie, offset, whence); }
static int asset_close(void* cookie) { AAsset_close((AAsset*)cookie); return 0; }

File::File(FileNode *node) : Communicator(node) {
    AAsset* asset = AAssetManager_open(assetManager, node->getPath(), 0);
    if (asset) id = (Handle) funopen(asset, asset_read, asset_write, asset_seek, asset_close);
    else LOGI("Asset %s not found", node->getPath());
    if (!id) id = (Handle) fopen(node->getPath(), "rb+");
}

#endif
