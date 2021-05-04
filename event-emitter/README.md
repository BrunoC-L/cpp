# Event Emitter

The observer design pattern is my favorite, it is quite simple, but extremely powerful and comes in many forms. One that I absolutely despise is when I see it implemented with "dynamic" types, like subscribing by string value of event type. I just want to PUKE. So Here I provide a way to subscribe to event classes.

There is basically 0 overhead and there are no limitations other than the fact that you CAN'T unsubscribe during your call. This will mess up the array of subscribers, please don't! I thought about making it so I would iterate the list in reverse, that way even if index 11 unsubscribes, moving down to index 10 is fine, but then realised that an idiot can always shoot himself in the foot and make the call to 11 unsubscribe 10, which just messes up the array anyway.

It might seem super weird at first when looking at the code but the reason there are macros is because they are extremely powerful! take a look at some event classes in <https://github.com/BrunoC-L/sfml-rs2d/tree/master/src/client/client> , for example <https://github.com/BrunoC-L/sfml-rs2d/blob/master/src/client/client/keyPressedEvent.h> Find me another way of defining events this easily and using them super easily aswell and I will eat my hat! The subscribers also use an RAII style of subscription so when they are destroyed they unsubscribe, that was just the cherry on top of the sundae if you ask me. Simply declare your observers in your class and whenever you want to subscribe call observer.set(lambda that takes event by reference); and there you go, all done! you can always unsubscribe manually, but from my experience most of the time you want listeners to keep listening.

## Proposed extension

I have not thought of a way to generalise this concept, neither have I given it much thought, but I think there might be a way to add parametrized subscriptions somehow. Events are nice but when you want 1000 objects to notify their 1000 listeners and in fact they are linked 1 to 1, its just a terrible idea to call 1000**2 times instead of 1000 times, but sometimes bad design decisions just stick. So I would like to come up with a general way to subscribe to certain criterias only.

I do not think its possible and rather what you do in that case is introduce a controller, which subscribes to the events and dispatches them properly, and the objects are made aware to the controller. There are too many options like wanting to be called when a value exceeds X, is X, X might be a string, a struct, a class, etc, a function even.. its just not possible to generalise it I think. There would be too much overhead, and it might be so complicated that it would go against KISS/YAGNI principles in most cases.

So yeah, if you have alot of subscribers, make sure you use a controller if they don't care about every event!
