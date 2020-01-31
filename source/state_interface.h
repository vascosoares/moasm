/**
 * @file state_interface.h
 * @author Vasco Soares (vascosoares.online@gmail.com)
 * @brief Public Interface for a state
 * @version 0.1
 * @date 2020-01
 * 
 */

#ifndef I_STATE_H
#define I_STATE_H


namespace moasm
{
    class IState
    {
       
        public:
            virtual ~IState();

            virtual bool active() const = 0;
            //virtual IStateMachine* machine() const = 0;
            //virtual State* parentState() const = 0;

            // Notifications
            virtual void activeChanged(bool active) = 0;
            virtual void entered() = 0;
            virtual void exited() = 0;

        protected:
            IState(IState* parent = nullptr);

            // Event triggers
            //virtual void onEntry(IEvent* event) = 0;
            //virtual void onExit(IEvent* event) = 0;

            //virtual bool event(IEvent* e) override = 0;
    };
}

#endif // I_STATE_H