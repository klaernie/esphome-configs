#include "esphome.h"

class SplitLight : public Component, public LightOutput {
	public:
	SplitLight( FloatOutput *front, FloatOutput *back ){
		this->front = front;
		this->back = back;
	}

	LightTraits get_traits() override {
		auto traits = LightTraits();
		traits.set_supports_brightness(true);
		return traits;
	}

	void write_state(LightState *state) override {
		float incoming;
		state->current_values_as_brightness( &incoming );

		float back = clamp(incoming*2, 0.0f, 1.0f);
		float front = clamp((incoming-0.5f)*2, 0.0f, 1.0f);

		ESP_LOGD("custom",
		    "incoming: %f, back: %f, front: %f",
		     incoming, back, front
		);

		this->front->set_level( front );
		this->back->set_level( back );
	}

	protected:
	FloatOutput *front;
	FloatOutput *back;
};
