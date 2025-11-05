#include "FileSystem.h"

Node::Node(const string& name, bool isDir, Node* parent, Node* leftmostChild, Node* rightSibling) {
	name_ = name;
	isDir_ = isDir;
	parent_ = parent;
	leftmostChild_ = leftmostChild;
	rightSibling_ = rightSibling;

}

Node::~Node() {
	// could add to this?

}

Node* Node::leftSibling() const {
	Node* cur = parent_->leftmostChild_;
	if (cur == this) {
		return nullptr;
	}

	while (cur->rightSibling_ != this) {
		cur = cur->rightSibling_;
	}
	return cur;
}

FileSystem::FileSystem() {
	root_ = new Node("",true,nullptr,nullptr,nullptr);
	curr_ = root_; //do i need this? should it be nullptr or root?
}

// DO NOT CHANGE
FileSystem::FileSystem(const string& testinput) {

	curr_ = root_ = new Node("", true);

	if (testinput == "1") {
		Node* e   = new Node("e"      , true , root_);
		Node* d   = new Node("d.txt"  , false, root_, nullptr, e);
		Node* c   = new Node("c.txt"  , false, root_, nullptr, d);
		Node* b   = new Node("b"      , true , root_, nullptr, c);
		Node* a   = new Node("a.txt"  , false, root_, nullptr, b);
		Node* ee  = new Node("ee.txt" , false, e);
		Node* bb2 = new Node("bb2"    , true , b);
		Node* bb1 = new Node("bb1"    , true , b, nullptr, bb2);
		Node* bbb = new Node("bbb.txt", false, bb1);
		root_->leftmostChild_ = a;
		b->leftmostChild_ = bb1;
		bb1->leftmostChild_ = bbb;
		e->leftmostChild_ = ee;
	}
	else if (testinput == "2") {
		Node* h = new Node("h"    , true , root_);
		Node* g = new Node("g.txt", false, root_, nullptr, h);
		Node* f = new Node("f"    , true , root_, nullptr, g);
		Node* e = new Node("e.txt", false, root_, nullptr, f);
		Node* d = new Node("d"    , true , root_, nullptr, e);
		Node* c = new Node("c.txt", false, root_, nullptr, d);
		Node* b = new Node("b"    , true , root_, nullptr, c);
		Node* a = new Node("a.txt", false, root_, nullptr, b);
		root_->leftmostChild_ = a;
	}
	else if (testinput == "3") {
		Node* c0 = new Node("c0", true, root_);
		Node* b0 = new Node("b0", true, root_, nullptr, c0);
		Node* a0 = new Node("a0", true, root_, nullptr, b0);
		Node* c1 = new Node("c1", true, a0);
		Node* b1 = new Node("b1", true, a0, nullptr, c1);
		Node* a1 = new Node("a1", true, a0, nullptr, b1);
		Node* c2 = new Node("c2", true, b0);
		Node* b2 = new Node("b2", true, b0, nullptr, c2);
		Node* a2 = new Node("a2", true, b0, nullptr, b2);
		Node* c3 = new Node("c3", true, c0);
		Node* b3 = new Node("b3", true, c0, nullptr, c3);
		Node* a3 = new Node("a3", true, c0, nullptr, b3);
		Node* c4 = new Node("c4", true, a1);
		Node* b4 = new Node("b4", true, a1, nullptr, c4);
		Node* a4 = new Node("a4", true, a1, nullptr, b4);
		root_->leftmostChild_ = a0;
		a0->leftmostChild_ = a1;
		b0->leftmostChild_ = a2;
		c0->leftmostChild_ = a3;
		a1->leftmostChild_ = a4;
	}
}

FileSystem::~FileSystem() {
	if (curr_ == root_) {
		delete root_;
	}
	else {
		delete root_;
		delete curr_;
	}


}

string FileSystem::cd(const string& path) {
	// could use switch see which is better
	if (path=="..") {
		if (curr_!=root_) {
			curr_ = curr_->parent_;
			return "";
		}
		return "invalid path";

	}
	if (path=="/") {
		curr_ = root_;
		return "";
	}

	string ls_contents = ls();

	if (ls_contents.find(path+"/")!=-1) {
		Node * subdir = curr_->leftmostChild_;
		while (subdir->name_ != path) {
			subdir = subdir->rightSibling_;
		}
		curr_ = subdir;
		return "";
	}
	return "invalid path";


}

// This is done for you as an example
string FileSystem::ls() const {

	string res;

	Node* tmp = curr_->leftmostChild_;
	while(tmp != nullptr) {
		res += tmp->name_;
		if (tmp->isDir_) res += "/\n";
		else res += "\n";
		tmp = tmp->rightSibling_;
	}
	if (res != "") res.pop_back(); // remove extra \n

	return res;
}

string FileSystem::pwd() const {
	string absolute_path = "";
	if (curr_ == root_) {
		return "/";
	}
	Node * tmp = curr_;
	while (tmp->parent_!=nullptr) {

		absolute_path = "/" + tmp->name_+ absolute_path;
		tmp = tmp->parent_;

	}

	return absolute_path;

}

string FileSystem::recursive_tree(Node* start_dir,string& res,int depth) const {


	Node * tmp = start_dir->leftmostChild_;
	while (tmp != nullptr) {
		res+="\n";
		res+=string(depth,' ');
		res += tmp->name_;
		if (tmp->isDir_) {
			res+="/";
			recursive_tree(tmp,res,depth+1);
		}
		tmp = tmp->rightSibling_;


	}

	return res;
}

string FileSystem::tree() const {
	string res;
	if (curr_ == root_) {
		res+="/";
	}
	else {
		res+=curr_->name_+"/";
	}

	return recursive_tree(curr_,res,1) ;


}

// modify to use left sibling instead of prev
string FileSystem::touch(const string& name) {
	Node * new_file = new Node(name,false,curr_,nullptr,nullptr);
	Node * tmp = curr_->leftmostChild_;
	if (tmp==nullptr) {
		curr_->leftmostChild_ = new_file;
		return "";
	}
	Node * prev = nullptr;
	while (tmp != nullptr) {
		prev = tmp;
		if (tmp->name_ == name) {
			return "file/directory already exists";
		}
		if (name.compare(tmp->name_) <= 0 and tmp == curr_->leftmostChild_) {
			curr_->leftmostChild_ = new_file;
			new_file->rightSibling_ = tmp;
			return "";

		}
		if (name.compare(tmp->name_) <= 0){
			prev->rightSibling_ = new_file;
			new_file->rightSibling_ = tmp;
			return "";
		}
		tmp = tmp->rightSibling_;

	}
	prev->rightSibling_ = new_file;
	return "";

}

string FileSystem::mkdir(const string& name) {
	Node * new_dir = new Node(name,true,curr_,nullptr,nullptr);
	Node * tmp = curr_->leftmostChild_;
	if (tmp==nullptr) {
		curr_->leftmostChild_ = new_dir;
		return "";
	}
	Node * prev = nullptr;
	while (tmp != nullptr) {
		prev = tmp;
		if (tmp->name_ == name) {
			return "file/directory already exists";
		}
		if (name.compare(tmp->name_) <= 0 and tmp == curr_->leftmostChild_) {
			curr_->leftmostChild_ = new_dir;
			new_dir->rightSibling_ = tmp;
			return "";

		}
		if (name.compare(tmp->name_) <= 0){
			prev->rightSibling_ = new_dir;
			new_dir->rightSibling_ = tmp;
			return "";
		}
		tmp = tmp->rightSibling_;

	}
	prev->rightSibling_ = new_dir;
	return "";

}

string FileSystem::rm(const string& name) {
	Node * tmp = curr_->leftmostChild_;

	while (tmp != nullptr) {
		if (tmp->name_ == name) {
			if (tmp->isDir_) {
				return "not a file";
			}
			if (tmp->leftSibling() != nullptr) {
				tmp->leftSibling()->rightSibling_ = tmp->rightSibling_;
				delete tmp;
				return "";
			}
			curr_->leftmostChild_ = tmp->rightSibling_;
			delete tmp;
			return "";
		}
		tmp = tmp->rightSibling_;
	}
	return "file not found";
}

string FileSystem::rmdir(const string& name) {
	Node * tmp = curr_->leftmostChild_;

	while (tmp != nullptr) {
		if (tmp->name_ == name) {
			if (!tmp->isDir_) {
				return "not a directory";
			}
			if (tmp->leftmostChild_ != nullptr) {
				return "directory not empty";
			}
			if (tmp->leftSibling() != nullptr) {
				tmp->leftSibling()->rightSibling_ = tmp->rightSibling_;
				delete tmp;
				return "";
			}
			curr_->leftmostChild_ = tmp->rightSibling_;
			delete tmp;
			return "";
		}
		tmp = tmp->rightSibling_;
	}
	return "directory not found";
}

string FileSystem::mv(const string& src, const string& dest) {
	// IMPLEMENT ME

	return ""; // dummy
}