# Event Emitter

The observer design pattern is my favorite, it is quite simple, but extremely powerful and comes in many forms.

This implementation offers typed event subscribers and emitters (not subscribing using enum event types or strings!)

output
> x: 1, y: 1, shift: true
> 
> x: 2, y: 2, shift: false
> 
> x: 2, y: 2, shift: false

I couldn't manage to forward the parameters to the event data member so i had to provide a macro `EVENT` to instead build the data in place for the constructor to take
