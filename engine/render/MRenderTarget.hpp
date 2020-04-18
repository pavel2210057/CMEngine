#ifndef MRENDERTARGET_HPP
#define MRENDERTARGET_HPP

class MRenderable;

class MRenderTarget abstract {
public:
	virtual void swap() const = 0;

	virtual void render(const MRenderable& renderable) const = 0;
};

#endif //!MRENDERTARGET_HPP