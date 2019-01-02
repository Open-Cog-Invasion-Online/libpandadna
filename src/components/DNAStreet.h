#ifndef _H_DNA_STREET_
#define _H_DNA_STREET_

#include "DNANode.h"

#define DUMP_COLOR(X) INDENTED_OUT << "color [ " << X.get_x() << " " << X.get_y() << " " << X.get_z() << " " << X.get_w() << " ]" << std::endl;

class BSPMaterial;

class EXPCL_DNA DNAStreet : public DNANode
{
    PUBLISHED:
        DNAStreet(const std::string& name);
        ~DNAStreet();
        
        WRITE_PDNA
        {
            DNANode::write_pdna(dg, false);
            
            dg.add_string(m_code);
            
            dg.add_string(m_street_material);
            dg.add_string(m_sidewalk_material);
            dg.add_string(m_curb_material);
            
            pack_color(dg, m_street_color);
            pack_color(dg, m_sidewalk_color);
            pack_color(dg, m_curb_color);
        }
        
        WRITE_DNA
        {
            DNANode::write_dna(out, false, indent);
            indent += 1;
            
            if (m_code.size())
                INDENTED_OUT << "code [ \"" << m_code << "\" ]" << std::endl;
            
            if (m_street_material.size())
            {
                INDENTED_OUT << "material [ \"" << m_street_material << "\" ]" << std::endl;
                if (m_sidewalk_material.size())
                {
                    INDENTED_OUT << "material [ \"" << m_sidewalk_material << "\" ]" << std::endl;
                    if (m_curb_material.size())
                    {
                        INDENTED_OUT << "material [ \"" << m_curb_material << "\" ]" << std::endl;
                    }
                }
            }
        
            if (m_street_color != LVecBase4f(1, 1, 1, 1))
            {
                DUMP_COLOR(m_street_color);
                if (m_sidewalk_color != LVecBase4f(1, 1, 1, 1))
                {
                    DUMP_COLOR(m_sidewalk_color);
                    if (m_curb_color != LVecBase4f(1, 1, 1, 1))
                    {
                        DUMP_COLOR(m_curb_color);
                    }
                }
            }
         
            indent -= 1;
            INDENTED_OUT << "]" << std::endl;
        }
        
        COMP_CODE(COMPCODE_STREET);
        COMP_NAME(street);

    public:
        virtual void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
        virtual void traverse(NodePath& np, DNAStorage* store);
        
    protected:
        const BSPMaterial *get_material(const std::string& material, DNAStorage* store);
        
    PROPERTY_STRING(code);
    PROPERTY_STRING(street_material);
    PROPERTY_STRING(sidewalk_material);
    PROPERTY_STRING(curb_material);
    PROPERTY_COLOR(street_color);
    PROPERTY_COLOR(sidewalk_color);
    PROPERTY_COLOR(curb_color);
    
    TYPE_HANDLE(DNAStreet, DNANode);
};

#endif
