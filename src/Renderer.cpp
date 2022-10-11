#include "Renderer.h"

Renderer::Renderer(std::vector<GLuint> attributes, GLuint max_sprites)
	: vbo_(0), vao_(0), max_sprites_(max_sprites)
{
	attrib_size_ = 0;
    for (auto att : attributes) attrib_size_ += att;


    // create storage in gpu
    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);

    glBindVertexArray(vao_);

    // set up vbo data inside gpu
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);

    auto stride = 0ull;
    for (auto i = 0ull; i < attributes.size(); ++i)
    {
        // set up attributes to decipher vbo in gpu
        glVertexAttribPointer(i, attributes[i], GL_FLOAT, GL_FALSE, attrib_size_ * sizeof(GLfloat), (GLvoid*)stride);
        glEnableVertexAttribArray(i);
        stride += sizeof(GLfloat) * attributes[i];
    }
}


Renderer::~Renderer()
{
	if (vbo_)
        glDeleteBuffers(1, &vbo_);
    if (vao_)
        glDeleteBuffers(1, &vao_);

    vbo_ = 0;
    vao_ = 0;
}

void Renderer::begin()
{
	current_material_ = nullptr;
}

void Renderer::end()
{
	flush();
}

void Renderer::draw(Rect dest_rect, Rect src_rect, Material& material)
{

	// 
	if((this->buffer_.size() >= this->max_sprites_ * 6 * this->attrib_size_ || !current_material_) ||
		this->current_material_->id != material.id)
	{
		this->flush();
		this->current_material_ = &material;
	}



	// first triangle

// bot left
	buffer_.push_back(dest_rect.x);
	buffer_.push_back(dest_rect.y + dest_rect.w);
	buffer_.push_back(src_rect.x);
	buffer_.push_back(src_rect.y + src_rect.w);

	// top right
	buffer_.push_back(dest_rect.x + dest_rect.z);
	buffer_.push_back(dest_rect.y);
	buffer_.push_back(src_rect.x + src_rect.z);
	buffer_.push_back(src_rect.y);

	// top left
	buffer_.push_back(dest_rect.x);
	buffer_.push_back(dest_rect.y);
	buffer_.push_back(src_rect.x);
	buffer_.push_back(src_rect.y);

	// second triangle

	// bot left
	buffer_.push_back(dest_rect.x);
	buffer_.push_back(dest_rect.y + dest_rect.w);
	buffer_.push_back(src_rect.x);
	buffer_.push_back(src_rect.y + src_rect.w);

	// bot right
	buffer_.push_back(dest_rect.x + dest_rect.z);
	buffer_.push_back(dest_rect.y + dest_rect.w);
	buffer_.push_back(src_rect.x + src_rect.z);
	buffer_.push_back(src_rect.y + src_rect.w);

	// top right
	buffer_.push_back(dest_rect.x + dest_rect.z);
	buffer_.push_back(dest_rect.y);
	buffer_.push_back(src_rect.x + src_rect.z);
	buffer_.push_back(src_rect.y);

}

void Renderer::flush()
{
	if (this->buffer_.empty()) return;

	if(!this->current_material_)
	{
		this->buffer_.clear();
		return;
	}

	this->current_material_->compile();
	this->current_material_->bind();

    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * this->buffer_.size(), this->buffer_.data(), GL_STATIC_DRAW);

	// draw triangle
	glDrawArrays(GL_TRIANGLES, 0, this->buffer_.size() / attrib_size_);

	// clear buffer for next cycle
	buffer_.clear();
}
