#include "Button.h"


Button::Button(SDL_Texture* _tex, SDL_Rect _rect)
:GuiElement(_tex, _rect)
{
	//-- Down Texture
	SDL_Surface *downSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, _rect.w, _rect.h, 16, 0, 0, 0, 1);
	SDL_FillRect(downSurface, NULL, SDL_MapRGB(downSurface->format, 0, 0, 0));

	SDL_Texture *downTexture = SDL_CreateTextureFromSurface(Window::Renderer(), downSurface);
	SDL_SetTextureAlphaMod(downTexture, 155);
	Button::downTexture = downTexture;
	SDL_FreeSurface(downSurface);

	//-- Hover Texture
	SDL_Surface *hoverSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, _rect.w, _rect.h, 8, 0, 0, 0, 1);
	SDL_FillRect(hoverSurface, NULL, SDL_MapRGB(hoverSurface->format, 0, 0, 0));

	SDL_Texture *hoverTexture = SDL_CreateTextureFromSurface(Window::Renderer(), hoverSurface);
	SDL_SetTextureAlphaMod(hoverTexture, 155);
	Button::hoverTexture = hoverTexture;
	SDL_FreeSurface(hoverSurface);
}

Button::Button(SDL_Rect _rect)
:GuiElement(nullptr, _rect)
{
	//-- Down Texture
	SDL_Surface *downSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, _rect.w, _rect.h, 16, 0, 0, 0, 1);
	SDL_FillRect(downSurface, NULL, SDL_MapRGB(downSurface->format, 0, 0, 0));

	SDL_Texture *downTexture = SDL_CreateTextureFromSurface(Window::Renderer(), downSurface);
	SDL_SetTextureAlphaMod(downTexture, 155);
	Button::downTexture = downTexture;

	//-- Hover Texture
	SDL_Surface *hoverSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, _rect.w, _rect.h, 8, 0, 0, 0, 1);
	SDL_FillRect(hoverSurface, NULL, SDL_MapRGB(hoverSurface->format, 0, 0, 0));

	SDL_Texture *hoverTexture = SDL_CreateTextureFromSurface(Window::Renderer(), hoverSurface);
	SDL_SetTextureAlphaMod(hoverTexture, 155);
	Button::hoverTexture = hoverTexture;

	//-- Regular Texture
	SDL_Surface *regularSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, _rect.w, _rect.h, 8, 0, 0, 0, 1);
	SDL_FillRect(regularSurface, NULL, SDL_MapRGB(regularSurface->format, 0, 0, 0));

	SDL_Texture *regularTexture = SDL_CreateTextureFromSurface(Window::Renderer(), regularSurface);
	SDL_SetTextureAlphaMod(regularTexture, 255);
	Button::texture = regularTexture;

	SDL_FreeSurface(downSurface);
	SDL_FreeSurface(hoverSurface);
	SDL_FreeSurface(regularSurface);
}

Button::~Button()
{
	Free();

	if (label != nullptr)
		delete label;

	SDL_DestroyTexture(downTexture);
	SDL_DestroyTexture(hoverTexture);
}

void Button::AddLabel(const std::string &_text, TTF_Font* _font, SDL_Color _color, bool center)
{
	SDL_Rect _rect = rect;
	_rect.x += 5;
	_rect.w -= (_rect.x - rect.x);

	if (center) {
		int* w = new int();
		int* h = new int();
		TTF_SizeText(_font, _text.c_str(), w, h);

		_rect.y += ((_rect.h - *h) / 6);
		_rect.h -= (_rect.y - rect.y);
	}

	label = new Label(_text, _rect, _font, _color);
	label->SetOffset(offset);
}
void Button::AddLabel(Label* _label)
{
	label = _label;
	label->SetOffset(offset);
}

Label* Button::GetLabel()
{
	if (label == nullptr)
		return nullptr;
	return label;
}

void Button::SetOffset(SDL_Rect _rect)
{
	GuiElement::SetOffset(_rect);
	if (label != nullptr)
		label->SetOffset(_rect);
}

void Button::SetPadding(SDL_Rect _rect)
{
	GuiElement::SetPadding(_rect);
	if (label != nullptr)
		label->SetPadding(_rect);
}

void Button::Update(double _time)
{
	if (Active) {
		GuiElement::Update(_time);
	}
}

void Button::Draw()
{
	if (Active) {
		GuiElement::Draw();

		if (label != nullptr)
			label->Draw();

		if (isPressedDown) {
			SDL_Rect rectangle = rect;
			rectangle.x += offset.x + padding.x;
			rectangle.y += offset.y + padding.y;

			SDL_RenderCopyEx(Window::Renderer(), downTexture, NULL, &rectangle, 0., NULL, flip);
		}
		else if (isHovering) {
			SDL_Rect rectangle = rect;
			rectangle.x += offset.x + padding.x;
			rectangle.y += offset.y + padding.y;

			SDL_RenderCopyEx(Window::Renderer(), hoverTexture, NULL, &rectangle, 0., NULL, flip);
		}
	}
}

void Button::OnMouseHover(SDL_MouseMotionEvent e)
{
	if (!Active) return;

	if (Intersects({ e.x, e.y, 1, 1 }))
	{
		isHovering = true;
		GuiElement::OnMouseHover(e);
	}
	else isHovering = false;
}
void Button::OnMouseClick()
{
	if (Intersects(APIEvents::MousePosition)) {}
	GuiElement::OnMouseClick();
}
void Button::OnMouseDown(SDL_MouseButtonEvent e)
{
	isPressedDown = true;
	GuiElement::OnMouseDown(e);
}
void Button::OnMouseUp(SDL_MouseButtonEvent e)
{
	isPressedDown = false;
	GuiElement::OnMouseUp(e);
}