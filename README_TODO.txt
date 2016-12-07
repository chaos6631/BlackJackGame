##TODO's
- Create a GUI method called GameMessage(string message) that outputs any feedback messages to the screen. Simple cout << message.

- Create a Game class method SaveGame(string playerName, double moneyTotal) that writes the name and total to a file inside of a Saved_Games folder.

- Create a Game class method OpenGame(string playerName) that searches the saved_games file for the player name and returns the total money for that player

- for all game functions replace couts with strings that are passed to GameMessage so that all screen output runs through the GUI class.



2. split hand ?? not sure if finished yet, haven't been able to get a hand eleigible to split
3. multiple decks
	-need a maxCard member, totalNumberOfDecks member
	-SetMaxCard() sets maxCard member based on decks chosen
	-Update the reshuffle method if needed
4. game saving
5. move all game functions to the game class
6. BeginGamePrompt() could list all saved games available and then ask you to choose one or start a new game
6. go through code and add any missing validation(need playername input validator that checks for at least 1 alpha char)
   need validation for when a user loses all of their money
7. clean up code by eliminating all DRY portions

