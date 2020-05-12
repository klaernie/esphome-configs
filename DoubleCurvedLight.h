#include "esphome.h"

class DoubleCurvedLight : public Component, public LightOutput {
	public:
	DoubleCurvedLight( FloatOutput *front, FloatOutput *back ){
		this->front = front;
		this->back = back;
	}

	LightTraits get_traits() override {
		auto traits = LightTraits();
		traits.set_supports_brightness(true);
		return traits;
	}

	void write_state(LightState *state) override {
		float total;
		state->current_values_as_brightness( &total );

		float cutover = 0.5;
		float p1 = std::min( total * 4, 0.15f );
		float p2 = std::min( std::max( (total - 0.3f) * 2, 0.f ), cutover);
		float p3 = std::max( total-cutover, 0.f ) * 0.35f * 2;
		float back = p1 + p2 + p3;

		float front = std::max(0.0f, total-0.5f) * 2;

		ESP_LOGD("custom",
		    "total: %f (%f), part 123: %f %f %f, back: %f, front: %f",
		     total, total*255.f, p1, p2, p3, back, front
		);

		this->front->set_level( front );
		this->back->set_level( back );
	}

	protected:
	FloatOutput *front;
	FloatOutput *back;
};
