#pragma once

#include "BaseState.h"
#include <typeinfo>

template <class StateType>
class State : public BaseState {
public:
	State() : _sm(nullptr) {
		_id = static_cast<StateID>(typeid(StateType).hash_code());
	}
	virtual void setParentStateMachine(BaseStateMachine* parentStateMachine) override final {
		_sm = parentStateMachine;
	}
	virtual StateID getStateID() override final { return _id; }
protected:
	BaseStateMachine* _sm;
private:
	StateID _id;
};
