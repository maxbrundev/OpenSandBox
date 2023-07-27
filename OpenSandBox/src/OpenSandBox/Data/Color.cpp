#include "OpenSandBox.h"

#include "OpenSandBox/Data/Color.h"

const OpenSandBox::Data::Color OpenSandBox::Data::Color::Red            = { 1.f, 0.f, 0.f };
const OpenSandBox::Data::Color OpenSandBox::Data::Color::Color::Green   = { 0.f, 1.f, 0.f };
const OpenSandBox::Data::Color OpenSandBox::Data::Color::Color::Blue    = { 0.f, 0.f, 1.f };
const OpenSandBox::Data::Color OpenSandBox::Data::Color::Color::White   = { 1.f, 1.f, 1.f };
const OpenSandBox::Data::Color OpenSandBox::Data::Color::Color::Black   = { 0.f, 0.f, 0.f };
const OpenSandBox::Data::Color OpenSandBox::Data::Color::Color::Grey    = { 0.5f, 0.5f, 0.5f };
const OpenSandBox::Data::Color OpenSandBox::Data::Color::Color::Yellow  = { 1.f, 1.f, 0.f };
const OpenSandBox::Data::Color OpenSandBox::Data::Color::Color::Cyan    = { 0.f, 1.f, 1.f };
const OpenSandBox::Data::Color OpenSandBox::Data::Color::Color::Magenta = { 1.f, 0.f, 1.f };

const OpenSandBox::Data::Color OpenSandBox::Data::Color::Color::EditorYellow = { 1.f, 0.8f, 0.01f };

OpenSandBox::Data::Color::Color(float p_r, float p_g, float p_b, float p_a) : r(p_r), g(p_g), b(p_b), a(p_a)
{
}

bool OpenSandBox::Data::Color::operator==(const Color& p_other) const
{
	return this->r == p_other.r && this->g == p_other.g && this->b == p_other.b && this->a == p_other.a;
}

bool OpenSandBox::Data::Color::operator!=(const Color& p_other) const
{
	return !operator==(p_other);
}
