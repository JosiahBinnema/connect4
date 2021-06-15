# Josiah's connect 4 ai  

This is my best attempt at a connect 4 ai (just for fun)


This is a work in progress, whenever I have spare time. I plan to implement the AI by evauating every position, then choosing the best path
Ideally I'll be able to implement Alpha-beta pruning first, then I'll move on to searching good moves first, then I'll ensure it remembers positions so it doesn't reevaluate the same position twice during one search. 

Likely I won't get a lot of this done, but if I can make an AI that uses alpha beta pruning and can beat me in connect 4. I'll call that a mad win



Journal of the mission:
June 8, 2021 - The AI is born. It evaluates at a depth of 0.5 and only stands a chance if it goes first.
June 12 - Wow, I really messed up. My old evaluation simply tried to pick the best move. I was trying to base the value of the position off of the value of the best move. However this really doesn't work. It doesn't allow you to accurately analyze future board states with minimax because it doesn't take opponent's moves into account. I had to do a rewrite basically everything I'd done for the AI logic. 
	I had some really grandios ideas with boolean arrays representing the 69 possible ways to connect 4, then only evaluating the ones that were still possibilities, but I realized it was going to be more computationally heavy to keep track of that than it was to just calculate all of the states. The only bit of optimization I did for this was to keep track of the highest column, and not bother with horizontals above that. (I think this is worth it) and also the vertical evaluation stops intelligently. All diagonals almost always required evaluation, so I just always evaluate all of them. 
June 15 - Talk about a sprint! I made a whole new evaluate position function today. I'm busy with other things in life, but maybe by the end of the week I'll be able to plug this into my minimax, then we're good to go!


