var path = require('path');
var args = process.argv.slice(2);

function getBuildGoal(goalName) {
    return require(path.join(__dirname, 'build-goals', goalName));
}

function buildGoal(goalName) {
    var goal = goals[goalName];

    if (!goal) {
        console.log('Skipping unknown build goal:', goalName);
    } else {
        goal.build();
    }
}

var goals = {
    ui     : getBuildGoal('ui'),
    engine : getBuildGoal('engine')
};


(args.length ? args : Object.keys(goals)).forEach(buildGoal);
