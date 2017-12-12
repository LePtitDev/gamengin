#ifndef ASSETS_H
#define ASSETS_H

#include <string>
#include <memory>
#include <vector>

class Asset {

    // Asset name
    std::string name;

    // Asset content
    std::shared_ptr<void> data;

public:

    // Basic constructor
    Asset(const char * name, const std::shared_ptr<void>& data) : name(name), data(data) {}

    // Get asset name
    const char * getName() {
        return name.c_str();
    }

    // Get content data
    template <typename T>
    T * getData() {
        return dynamic_cast<T *>(data.get());
    }

    // Get content data
    template <typename T>
    const T * getData() const {
        return dynamic_cast<const T *>(data.get());
    }

private:

    // Assets list
    static std::vector<Asset *>& GetAssetList() {
        static std::vector<Asset *> assets;
        return assets;
    }

public:

    // Get asset list count
    static unsigned int GetCount() {
        return (unsigned int)GetAssetList().size();
    }

    // Get asset list
    static Asset ** GetAssets() {
        return GetAssetList().data();
    }

    // Find an asset
    static Asset * Find(const char * name) {
        for (auto it : GetAssetList()) {
            if (it->name == name)
                return it;
        }
        return 0;
    }

    // Indicate if an asset exists
    static bool Exists(const char * name) {
        return Find(name) != 0;
    }

    // Remove an asset
    static void Remove(const char * name) {
        std::vector<Asset *>& assets = GetAssetList();
        for (unsigned int i = 0, sz = (unsigned int)assets.size(); i < sz; i++) {
            if (assets[i]->name == name) {
                delete assets[i];
                assets.erase(assets.begin() + i);
                break;
            }
        }
    }

    // Clear assets
    static void Clear() {
        for (auto it : GetAssetList())
            delete it;
        GetAssetList().clear();
    }

    // Load a new asset
    static Asset * Load(const char * name, const char * filename);

    // Load an image
    static Asset * LoadPNG(const char * name, const char * filename);

    // Load a 3D model
    static Asset * LoadPLY(const char * name, const char * filename);

};

#endif // ASSETS_H
