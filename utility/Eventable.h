//
// Created by Meevere on 07.11.2021.
//

#ifndef EVENTABLE_H
#define EVENTABLE_H

#include <functional>
#include <list>

/**
 * This is the class for Eventable objects. Here is an example of usage
 * Suppose you have a generic Button class for handling clicks and doing something afterwards
 *
 * How would you usually make it (imho)

class Button {
    void check_if_inside(Vectof2f pos);
public:
    // handler is public because it's free to change
    std::function<void(Vector2f)> handler;

    void press(Vector2f pos);
};

 *
 * And in code you would do it like this
 *

//some insides of init
Button exit{params};
Button enter{params};

std::array<Button> buttons {exit, enter};

//and in loop
for(auto &button : buttons){
    button.press(mouse_pos);
}

 *
 * And immediately some questions arise :
 *      what if you would need to need another action on press of a button?
 *      how I would handle millions of my buttons? call all of them implicitely in a loop?
 *
 * Well, this Eventable helps you with that kind of problem!
 *
 *
 * @tparam C
 */
template <class CEvent>
class Eventable {
    // And a corresponding typedef
    typedef typename CEvent::EventType CEventType;

    struct Functor {
        std::function<void(const CEvent&)> func;

        void operator ()(const CEvent& event) {
            func(event);
        }

        int id;

        Functor(const std::function<void(const CEvent &)> &func, int id) : func(func), id(id) {}
    };

    /**
     * In pair:
     *  function - handler
     *  int - id of function (for removal)
     */
    std::list<Functor> event_listeners{};
    int last_id = 0;
public:
    /**
     * There we assign a listener to ALL events that happen to Eventable
     * @param func
     */
    int add_event_listener(const std::function<void(const CEvent&)>& func){
        event_listeners.emplace_back(func, last_id);
        return last_id++;
    }

    /**
     * There we assign a listener to ALL events that happen to Eventable
     * And that func doesn't even take an argument
     * @param func
     */
    int add_event_listener(const std::function<void()>& func){
        return add_event_listener([func](const CEvent& e){ func(); });
    }

    /**
     * @param type
     * @param func
     */
    int add_event_listener(CEventType type, const std::function<void(const CEvent&)>& func) {
        return add_event_listener([func, type](const CEvent& e){
            if(e.type == type){
                func(e);
            }
        });
    }

    /**
     * @param type
     * @param func
     */
    int add_event_listener(CEventType type, const std::function<void()>& func) {
        return add_event_listener(type, [func](const CEvent& e){ func(); });
    }

    /**
     *
     * @param id // id of the function
     * @return // true if removal is successful
     */
    bool remove_event_listener(int id){
        auto old_size = event_listeners.size();
        event_listeners.remove_if([id](const Functor& func){
            return func.id == id;
        });
        return old_size != event_listeners.size();
    }
    /**
     * There we throw/evoke event to all event handlers
     * @param e
     */
    void evoke(const CEvent& e){
        for( auto& func : event_listeners ){
            func(e);
        }
    }
};


#endif //EVENTABLE_H
