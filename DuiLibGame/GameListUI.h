
#include <vector>
#include <UIlib.h>

extern double CalculateDelay(double state);

class GameListUI : public DuiLib::CListUI
{
public:
	enum { SCROLL_TIMERID = 10 };
	struct NodeData
	{
		int _level;
		bool _expand;
		DuiLib::CDuiString _text;
		DuiLib::CListLabelElementUI *_pListElement;
	};
	class Node
	{
		typedef std::vector <Node *> Children;
		Children _children;
		Node *_parent;
		NodeData _data;

	private:
		void set_parent(Node *parent);
	public:
		Node();
		explicit Node(NodeData t);
		Node(NodeData t, Node *parent);
		~Node();
		NodeData &data();
		int num_children() const;
		Node *child(int i);
		Node *parent();
		bool has_children() const;
		void add_child(Node *child);
		void remove_child(Node *child);
		Node *get_last_child();
	};

	GameListUI();
	~GameListUI();
	bool Add(DuiLib::CControlUI *pControl);
	bool AddAt(CControlUI* pControl, int iIndex);
	bool Remove(CControlUI* pControl);
	bool RemoveAt(int iIndex);
	void RemoveAll();
	void SetVisible(bool bVisible = true);
	void SetInternVisible(bool bVisible = true);
	void DoEvent(DuiLib::TEventUI& event);
	Node* GetRoot();
	Node* AddNode(LPCTSTR text, Node* parent = NULL);
	bool RemoveNode(Node* node);
	void ExpandNode(Node* node, bool expand);
	SIZE GetExpanderSizeX(Node* node) const;

private:
	Node* _root;

	LONG m_dwDelayDeltaY;
	DWORD m_dwDelayNum;
	DWORD m_dwDelayLeft;
};