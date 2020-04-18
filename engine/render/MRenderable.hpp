#ifndef MRENDERaBLE_HPP
#define MRENDERaBLE_HPP

class MRenderTarget;

class MRenderable abstract {
public:
	virtual void render(const MRenderTarget& target) const = 0;
};

#endif //!MRENDERaBLE_HPP