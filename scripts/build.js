var args = process.argv.slice(2);

var goals = {
    ui: require(__dirname + '/build-goals/ui')
};

function buildGoal(goalName) {
    var goal = goals[goalName];

    if (!goal) {
        console.log('Skipping unknown build goal:', goalName);
    } else {
        console.log('Building', goalName);
        goal.build();
    }
}

(args.length ? args : Object.keys(goals)).forEach(buildGoal);
