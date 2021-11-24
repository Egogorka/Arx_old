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

    std::list<std::function<void(const CEvent&)>> event_listeners{};
public:
    /**
     * There we assign a listener to ALL events that happen to Eventable
     * @param func
     */
    void add_event_listener(const std::function<void(const CEvent&)>& func){
        event_listeners.push_back(func);
    }

    /**
     * There we assign a listener to ALL events that happen to Eventable
     * And that func doesn't even take an argument
     * @param func
     */
    void add_event_listener(const std::function<void()>& func){
        add_event_listener([func](const CEvent& e){ func(); });
    }

    /**
     * @tparam CChild - Child of CEvent
     * @param type
     * @param func
     */
    void add_event_listener(CEventType type, const std::function<void(const CEvent&)>& func) {
        event_listeners.push_back([func, type](const CEvent& e){
            if(e.type == type){
                func(e);
            }
        });
    }

    /**
     * @tparam CChild - Child of CEvent
     * @param type
     * @param func
     */
    template<class CChild>
    void add_event_listener(CEventType type, const std::function<void()>& func) {
        add_event_listener(type, [func](const CEvent& e){ func(); });
    }

    /**
     * There we throw/evoke event to all event handlers
     * @param e
     */
    void evoke(CEvent e){
        for( auto& func : event_listeners ){
            func(e);
        }
    }
};


#endif //EVENTABLE_H
