#define GEN_CREATOR(name, args...) \
	node* create_##name(args);

#define CREATOR_IMPL_DEF(name, args...) \
	node* node::create_##name(args)

#define CREATOR_IMPL(name, args...)    \
	node* n		= new obj::name(args); \
	n->m_root	= false;               \
	n->m_parent = this;                \
	m_children.push_back((node*)n);    \
	return n;
