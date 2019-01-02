#include "DNAStreet.h"

#include <bsp_material.h>

TypeHandle DNAStreet::_type_handle;

DNAStreet::DNAStreet(const std::string& name): DNANode(name), m_code(""),
                                               m_street_material(""),
                                               m_sidewalk_material(""),
                                               m_curb_material(""),
                                               m_street_color(LVecBase4f(1)),
                                               m_sidewalk_color(LVecBase4f(1)),
                                               m_curb_color(LVecBase4f(1))
{
}

DNAStreet::~DNAStreet()
{
}

void DNAStreet::make_from_dgi(DatagramIterator& dgi, DNAStorage* store)
{
    DNANode::make_from_dgi(dgi, store);
    m_code = dgi.get_string();
    m_street_material = dgi.get_string();
    m_sidewalk_material = dgi.get_string();
    m_curb_material = dgi.get_string();
    m_street_color = DGI_EXTRACT_COLOR;
    m_sidewalk_color = DGI_EXTRACT_COLOR;
    m_curb_color = DGI_EXTRACT_COLOR;
}

void DNAStreet::traverse(NodePath& np, DNAStorage* store)
{
    NodePath result = store->find_node(m_code);
    if (result.is_empty())
    {
        raise_code_not_found();
        return;
    }
    
    NodePath _np = result.copy_to(np);
    _np.set_name(m_name);
    
    const BSPMaterial *street_material = get_material(m_street_material, store);
    const BSPMaterial *sidewalk_material = get_material(m_sidewalk_material, store);
    const BSPMaterial *curb_material = get_material(m_curb_material, store);
    
    NodePath street_node = _np.find("**/*_street");
    NodePath sidewalk_node = _np.find("**/*_sidewalk");
    NodePath curb_node = _np.find("**/*_curb");
    
    if (!street_node.is_empty() && street_material)
    {
        street_node.set_attrib(BSPMaterialAttrib::make(street_material), 1);
        street_node.set_color_scale(m_street_color);
    }
    
    if (!sidewalk_node.is_empty() && sidewalk_material)
    {
        sidewalk_node.set_attrib(BSPMaterialAttrib::make(sidewalk_material), 1);
        sidewalk_node.set_color_scale(m_sidewalk_color);
    }
    
    if (!curb_node.is_empty() && curb_node)
    {
        curb_node.set_attrib(BSPMaterialAttrib::make(curb_material), 1);
        curb_node.set_color_scale(m_curb_color);
    }
    
    _np.set_pos_hpr_scale(m_pos, m_hpr, m_scale);

    _np.clear_model_nodes();
    _np.flatten_strong();
}
        
const BSPMaterial *DNAStreet::get_material(const std::string& material, DNAStorage* store)
{
    if (!material.size())
        return NULL;
   
    const BSPMaterial *tex = store->find_material(material);
    if (!tex)
    {
        raise_code_not_found(material.c_str());
        return NULL;
    }

    return tex;
}
