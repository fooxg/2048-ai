# 2048 AI
This repository will consist fast 2048 that can be played in console and few AI algorithms that can be compered against each other.

## Updates

Now it contains working game in console (without winning conditions)

## TODO

- Add all neural components
- Add scoring system for the game
- Add game condition to win and lose game
- Add fitness function

## All Ai approaches and strategies

- [x] Random shuffle
- [ ] Random shuffle only going up and both sides (can be done in minutes)
- [ ] Neural network with evolution trainning
- [ ] Neural network with Q learning
- [ ] MinMax with different predicted number of moves
- [ ] Expectiminimax
- [ ] Basic hardcode algorithm (to compare)

## Random shuffle

This approach takes random number to select move and preforms it. With added additional preffered direction algorithm will try to push all cells to one side to maximize chance of winning (simple strategy used by players)

## Neural network

Well it is kinda self explanatory. In this particular case array of whole game board is given with score and the output is array of moves.

## MinMax

Find best move by looking at possible outcomes (simulate x next game states)

## Expectiminimax

Really similar to MinMax but added few corrections to uncertainties due to random values.

## Hardcode algorithm

Works similar to random shuffle with limited one way. This algorithm will try to do some basic stuff to follow zig zag pattern starting from top and slowly descending in order.
