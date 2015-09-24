iot_api = DDP.connect('https://iot-api.scalingo.io/');
coffeecups = new Meteor.Collection('coffeecups', iot_api);

if (Meteor.isClient) {
  Template.coffeecups.helpers({
    counter: function () {
      return coffeecups.find().count();
    },
    counter_020: function () {
      return coffeecups.find({"location": "q020"}).count();
    },
    counter_070: function () {
      return coffeecups.find({"location": "q070"}).count();
    },
    daycounter_020: function() {
      d = new Date();
      d.setUTCHours(0,0,0,0);
      return coffeecups.find(
        {
          published_at: { $gte: d.toISOString() },
          location: "q020"
        }
      ).count();
    },
    first_020: function() {
      return coffeecups.findOne({
                published_at: { $gte: d.toISOString() },
                location: "q020"
              });
    },
    latest_020: function() {
      return coffeecups.findOne({ location: "q020" }, { sort: { published_at: -1 }});
    },
    latest: function () {
      return coffeecups.findOne({}, { sort: { published_at: -1 }});
    }
  });
}
