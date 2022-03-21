## Text-Game-ngine

Web engine for text games written in React. Supports stories provided in .json file formatted as follows:
```
{
    "title": "foo",                     // Title of our story
    "quests": {
        "startQuestID": 0,              // ID of question starting the story
        "storyline": [                  // Array of situations in current story. As long as
            {                           // each question has unique ID. There can be as many of them as you want. 
                "id": 0,                    // ID of this question
                "text": "bar...",           // Any text describing current situation
                "choices": [                // Array of choices possible in current situation
                    {
                        "text": "baz"       // Description of choice
                        "chance": 0.3,      // Chance (optional) of success (from 0 - 1 interval)
                        "success": 1,       // ID of next question when action succeeds
                        "failure": 404      // ID of next question when action fails (optional)
                    },
                    {
                        "text":"quz",       // Same as above. Every question can have any number of choices.
                        "success": 2
                    }
                ]
            }
        ]
    }
}
```

Project has been bootstraped with Create-React-App, thus any scripts, dependencies and configs are left as-is.
You can use `npm install` to install any required dependencies and `npm start` to launch webapp server.