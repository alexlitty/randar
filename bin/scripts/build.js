require('./init');
global.async  = require('async');
global.glob   = require('glob');
global.mkdirp = require('mkdirp');

// Make a list of possible goals.
function getBuildGoal(goalName) {
    return require(path.join(__dirname, 'build-goals', goalName));
}

var possibleGoals = {
    ui      : getBuildGoal('ui'),
    adapter : getBuildGoal('adapter')
};

// Parse arguments.
var args    = process.argv.slice(2);
var goals   = [];
var options = { };

args.forEach(function(arg) {
    if (arg === 'rebuild=yes') {
        options.rebuild = true;
    }

    else {
        goals.push(arg);
    }
});

// If no goals are provided, use all possible goals.
if (!goals.length) {
    goals = Object.keys(possibleGoals);
}

// Builds the desired goals.
function build(done) {
    async.parallel(
        goals.map(function(goalName) {
            return function(done) {
                var goal = possibleGoals[goalName];
                if (!goal) {
                    return;
                }

                goal.build(options, done);
            }
        }),

        function(err) {
            if (err) {
                console.error(err);
            }

            done && done(err);
        }
    );
}

if (require.main === module) {
    build();
} else {
    module.exports = build;
}
