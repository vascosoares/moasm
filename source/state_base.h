#ifndef STATE_BASE_H
#define STATE_BASE_H


namespace moasm
{
    class StateBase
    {
       
        public:
            virtual ~StateBase();

            virtual bool active() const;
            //virtual IStateMachine* machine() const = 0;
            //virtual State* parentState() const = 0;

            // Notifications
            virtual void activeChanged(bool active);
            virtual void entered();
            virtual void exited();

        protected:
            StateBase(StateBase* parent = nullptr);

            // Event triggers
            //virtual void onEntry(IEvent* event) = 0;
            //virtual void onExit(IEvent* event) = 0;

            //virtual bool event(IEvent* e) override = 0;
    };
}

#endif // STATE_BASE_H