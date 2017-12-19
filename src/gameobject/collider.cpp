#include "collider.h"
#include "../assets/scene.h"

namespace ColliderExtra {

void PropagateRaycast(const Ray& ray, std::vector<std::pair<Collider *, float>>& res, GameObject * gm) {
    Collider * coll = gm->getComponent<Collider>();
    float dist;
    if (coll != 0 && coll->intersectRay(ray, dist)) {
        int insert_pos = 0;
        for (int i = 0, sz = (int)res.size(); i < sz; i++) {
            if (res[i].second > dist)
                break;
        }
        res.insert(res.begin() + insert_pos, { coll, dist });
    }
    for (int i = 0, sz = gm->childrenCount(); i < sz; i++)
        PropagateRaycast(ray, res, gm->getChild(i));
}

}

std::vector<std::pair<Collider *, float>> Collider::Raycast(const Ray& ray) {
    std::vector<std::pair<Collider *, float>> result;
    int count = Scene::main->getCount();
    GameObject ** objects = Scene::main->getObjects();
    for (int i = 0; i < count; i++)
        ColliderExtra::PropagateRaycast(ray, result, objects[i]);
    return result;
}
