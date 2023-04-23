#ifndef EVENT_H
#define EVENT_H

class Event{
  public:
   /* some events */

    enum UNIT_TYPE{
      WARRIOR,
      MAGIC,
      SIEGE
    };

    enum EventType{
       UNIT_DIE,
       UNIT_CREATE,
       /* .... */
    };

    EventType type;

    union{
      UNIT_TYPE unitType;

      /* ... */
    };

};

#endif // EVENT_H
