#ifndef WORLD_H
#define WORLD_H

#include <memory>
#include <map>

class World;
class WorldObjectsCollection;

#include "model.h"
#include "primitives.h"
#include "objects.h"
#include "model/intersection.h"


class WorldPlane : public WorldObject
{
private:
    Distance distance_;

public:
    WorldPlane(World* const, const Distance&);
    virtual WorldObjectView* get_view(const Coordinates&, const UnitVector&);
    virtual Shape* get_shape(const Coordinates&, const UnitVector&);
};

struct Position
{
    Coordinates coordinates;
    UnitVector direction;
};

class WorldObjectsCollection
{
private:
    typedef std::pair<WorldObject*, Position> element;
    Model* const model_;
    std::map<WorldObject*, Position> objects_;

public:
    WorldObjectsCollection(Model* const model);
    ~WorldObjectsCollection();
    class iterator
    {
    private:
        std::map<WorldObject*, Position>::const_iterator iterator_;
    public:
        iterator(const std::map<WorldObject*, Position>::const_iterator& iterator)
        {
            iterator_ = iterator;
        }
        iterator& operator++() {++iterator_;return *this;}
        iterator operator++(int) {iterator tmp(*this); operator++(); return tmp;}
        bool operator==(const iterator& rhs) {return iterator_==rhs.iterator_;}
        bool operator!=(const iterator& rhs) {return iterator_!=rhs.iterator_;}
        WorldObject* operator*() {return iterator_->first;}
    };
    iterator begin() const;
    iterator end() const;
    bool add(WorldObject*, const Coordinates&, const UnitVector&);
    void remove(WorldObject*);
    const WorldObjectViewCollection get_view() const;
};


class World
{
private:
    WorldObjectsCollection objects_;

public:
    World(Model* const);
    const AbsoluteTime get_next_event_time() const;
    const std::vector<std::shared_ptr<WorldObjectView>> get_objects() const;
};

#endif
