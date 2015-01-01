if (typeof(window) === 'undefined') {
  // TODO: shim in duktape
  function consoleShim() {
    print(Array.prototype.join.call(arguments, ' '));
  }

  var console = {};
  ['debug', 'log', 'info', 'warn'].forEach(function(i) {
    console[i] = consoleShim;
  });
}

var React = require('react');

var A = React.createClass({
  render: function() {
    return React.DOM.div(null, 'this is my content');
  }
});

var B = React.createClass({
  render: function() {
    return React.DOM.div(null, '☃');
  }
});

if (typeof(window) === 'undefined') {
  // option 1 -> capture markup directly
  //   I don't like this because it is super mysterious
  //capture(React.renderToString(React.createElement(A)));

  // option 2 -> somehow get webpack bundle file to return a value (??)
  //   this is probably not happening

  // option 3 -> somehow get webpack bundle file to make React available in global scope
  global.React = React;
  global.ReactElements = {
    'A': A,
    'B': B
  };
  // option 3b -> somehow call React.renderToString from C
}
