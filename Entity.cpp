#include "Entity.h"
#include <iostream>

VertexBuffer::VertexBuffer(const void* data, unsigned long size){
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    std::cout << "Initialized" << std::endl;
}

VertexBuffer::~VertexBuffer(){
    glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Bind() const {
    std::cout << "Binded" << std::endl;
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexArray::VertexArray(){
    std::cout << "Entity created" << std::endl;
    glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray(){
    glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::Bind() const{
    glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const{
    glBindVertexArray(0);
}

void VertexArray::AddBuffer(const VertexBuffer* vb, const VertexBufferLayout& layout){

    Bind();

    vb -> Bind();

    // we get vertex buffer elements
    const auto& elements = layout.GetElements();

    unsigned int offset = 0;

    for(unsigned int i = 0; i < elements.size(); i++){

        const auto& element = elements[i];

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(
            0,
            element.count,      // size
            element.type,       // type
            element.normalized ? GL_TRUE : GL_FALSE, // normalized?
            sizeof(Vertex),     // stride - THAT MAY BE WRONG!
            (const void*) 0     // array buffer offset
            );

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(
            1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            element.count,                    // size
            element.type,                     // type
            element.normalized ? GL_TRUE : GL_FALSE, // normalized?
            sizeof(Vertex),                   // stride - THAT MAY BE WRONG!
            (void*) offsetof(Vertex, Color)   // array buffer offset
            );

        // offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }

}

// This should be a template
Entity::Entity(std::vector<Vertex>& vertices){

    va = new VertexArray();
    va -> Bind();

    VertexBuffer* vb = new VertexBuffer(&vertices[0], vertices.size() * sizeof(Vertex));

    VertexBufferLayout layout;

    layout.Push<Vertex>(3);

    va -> AddBuffer(vb, layout);
}
