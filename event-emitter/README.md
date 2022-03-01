# Event Emitter

The observer design pattern is my favorite, it is quite simple, but extremely powerful and comes in many forms. One that I absolutely despise is when I see it implemented with "dynamic" types, like subscribing using a string of event type and receiving an Event* you then cast. This implementation offers typed event subscribers and emitters.

output
> x: 1, y: 2, shift: 1
> 
> x: 4, y: 5, shift: 0
