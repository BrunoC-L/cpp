# OnExit

this is especially useful if you have many exits in a function and want to make damn sure you free some ressource, destroy something, change the state of an object, etc, whatever happens during the function call, so you just build a NAMED OnExit object and whenever the scope ends the lambda will be called.
