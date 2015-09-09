iot_api = DDP.connect('https://iot-api.scalingo.io/');
coffeecups = new Meteor.Collection('coffeecups', iot_api);

if (Meteor.isClient) {
  Template.coffeecups.helpers({
    counter: function () {
      return coffeecups.find().count();
    },
    counter_020: function () {
      return coffeecups.find({"location": "Q020"}).count();
    },
    counter_070: function () {
      return coffeecups.find({"location": "Q070"}).count();
    },
    latest: function () {
      return coffeecups.findOne({}, { sort: { timestamp: -1 }});
    }
  });
}
