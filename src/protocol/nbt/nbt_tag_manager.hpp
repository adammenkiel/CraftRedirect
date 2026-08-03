#include "protocol/nbt/nbt_base.hpp"
#include "protocol/nbt/tags/nbt_tag_end.hpp"
#include "protocol/nbt/tags/nbt_tag_byte.hpp"
#include "protocol/nbt/tags/nbt_tag_short.hpp"
#include "protocol/nbt/tags/nbt_tag_int.hpp"
#include "protocol/nbt/tags/nbt_tag_long.hpp"
#include "protocol/nbt/tags/nbt_tag_float.hpp"
#include "protocol/nbt/tags/nbt_tag_double.hpp"
#include "protocol/nbt/tags/nbt_tag_byte_array.hpp"
#include "protocol/nbt/tags/nbt_tag_string.hpp"
#include "protocol/nbt/tags/nbt_tag_list.hpp"
#include "protocol/nbt/tags/nbt_tag_compound.hpp"
#include "protocol/nbt/tags/nbt_tag_int_array.hpp"

class nbt_tag_manager {
    public:
        static std::shared_ptr<nbt_base> get_tag_by_id(int id) {
            switch(id) {
                case 0: {
                    nbt_tag_end tag;
                    return std::make_shared<nbt_tag_end>(tag);
                }
                case 1: {
                    nbt_tag_byte tag;
                    return std::make_shared<nbt_tag_byte>(tag);
                }
                case 2: {
                    nbt_tag_short tag;
                    return std::make_shared<nbt_tag_short>(tag);
                }
                case 3: {
                    nbt_tag_int tag;
                    return std::make_shared<nbt_tag_int>(tag);
                }
                case 4: {
                    nbt_tag_long tag;
                    return std::make_shared<nbt_tag_long>(tag);
                }
                case 5: {
                    nbt_tag_float tag;
                    return std::make_shared<nbt_tag_float>(tag);
                }
                case 6: {
                    nbt_tag_double tag;
                    return std::make_shared<nbt_tag_double>(tag);
                }
                case 7: {
                    nbt_tag_byte_array tag;
                    return std::make_shared<nbt_tag_byte_array>(tag);
                }
                case 8: {
                    nbt_tag_string tag;
                    return std::make_shared<nbt_tag_string>(tag);
                }
                case 9: {
                    nbt_tag_list tag;
                    return std::make_shared<nbt_tag_list>(tag);
                }
                case 10: {
                    nbt_tag_compound tag;
                    return std::make_shared<nbt_tag_compound>(tag);
                }
                case 11: {
                    nbt_tag_int_array tag;
                    return std::make_shared<nbt_tag_int_array>(tag);
                }
                default:
                    return nullptr;
            }
        }
};