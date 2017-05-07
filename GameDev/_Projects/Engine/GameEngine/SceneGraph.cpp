#include "SceneGraph.h"
#include "ResourceManager.h"
#include <stack>


SceneGraph::SceneGraph(string rootName, GameObject* root) {
	_scene = new Tree(rootName, root);
	//Instantiate a heap render list so that there is always one object in the static list
	_renderList = new RenderList(ResourceManager::getShader("default"));
}

SceneGraph::~SceneGraph(){
	clearScene();
	_scene->~Tree();
}

void SceneGraph::addToScene(std::string key, GameObject* obj) {
	_scene->addNode(key, obj);
}

void SceneGraph::addToSceneAsChildOf(Tree::Leaf* parent, std::string key, GameObject* obj) {
	_scene->addNodeAsChild(key, obj, parent);
}

void SceneGraph::removeSprite(std::string key) {
	_scene->findAndRemoveNode(key);
}

GameObject* SceneGraph::find(std::string key) {
	if (key == "root")
		return (GameObject*)_scene->root->data;
	else {
		Tree::Leaf* node = _scene->findNode(key);
		return (GameObject*)node->data;
	}
}

GameObject* SceneGraph::findChildinParent(Tree::Leaf* parent, std::string key) {
	Tree::Leaf* node = _scene->findNodeInChildren(parent, key);
	return (GameObject*)node->data;
}
void SceneGraph::clearScene() {
	_scene->clear();
}


void SceneGraph::createRenderList(){
	//reset the renderList
	RenderList::clearShaderList();
	Tree::Leaf* itr = _scene->root;
	while (itr != nullptr) {
		//Get a pointer to the current object
		GameObject* objPtr = (GameObject*)itr->data;
		//get the shader applied to that object
		Material* currentMaterial = objPtr->getMaterial();
		if (currentMaterial == nullptr) {
			currentMaterial = ResourceManager::getMaterial("default");
			objPtr->attachMaterial(currentMaterial);
		}
		GLSLProgram* currentShader = currentMaterial->getShaderProgram();

		//Get the renderList pointer containing the current shader we are looking at
		RenderList* rendListPtr = RenderList::getRenderListPointer(currentShader);
		//if the pointer returns null then there isnt a list for this shader type yet so create a new one
		if (rendListPtr == nullptr)
			rendListPtr = new RenderList(currentShader);
		//add the object to the render list that is now either been found as one in the shader list or has been created and added to it
		rendListPtr->addObject(objPtr);

		//after adding the object to the render list we can move down the tree...

		//Move to Child?
		if (itr->child != nullptr)
			itr = itr->child;
		//Move to sibling?
		else if (itr->next != nullptr)
			itr = itr->next;
		else {
			//End of a branch?
			Tree::Leaf* itr2 = itr->parent;
			while (itr2->parent != nullptr) {
				//Parent have siblings?
				if (itr2->parent->next != nullptr)
					itr = itr2->parent->next;
				else
					//Nope move up the branch
					itr2 = itr2->parent;
			}
			itr = nullptr;
		}

	}
}
//sorting to the renderlist would probably happen here 
void SceneGraph::updateScene() {
	stack<glm::mat4> matrixStack = stack<glm::mat4>();
	//push an identity matrix onto the stack, ensuring there is at least one object on it at all times
	matrixStack.push(glm::mat4(1.0f));
	//set an iterator to the root node of the tree for traversal
	Tree::Leaf* currNode = _scene->root;

	//loop through the tree and update children of the root
	while (currNode != nullptr) {
		//QUESTION #1: NEED AN UPDATE?! YES->LOGIC, NO->PASS//
		//Y:  Update node, and flag all the children of that node that they now need their matrix updated aswell.  Any indirect parenting can be ignored.
		GameObject* objPtr = (GameObject*)currNode->data;

		if (objPtr->needsUpdate()) {
			//Update the node
			objPtr->update(matrixStack.top());
			//Compount the node matrix with that of its parent (the parent transforms will be saved onto the stack, in the case of the root node the stack will only have an identity on top)
			//Notify the children, if the node has any.
			if (currNode->child != nullptr) {
				Tree::Leaf* itr = currNode->child;
				GameObject* objPtr2;
				while (itr != nullptr) {
					objPtr2 = (GameObject*)itr->data;
					objPtr2->flagForUpdate();
					itr = itr->next;
				}
			}
		}
		//END: QUESTION #1//

		//QUESTION #2: DO WE HAVE KIDS?!  YES->LOOPS NO->QUESTION_#3//
		//We are now up to date, and all our children know about it.  However we need to save our transform onto the stack so our kids can refrence it!  If we are a parent save our matrix onto the stack, otherwise we have no children so no object will need our transform.
		if (currNode->child != nullptr) {
			//Save the matrix of the parent onto the stack
			matrixStack.push(objPtr->getTransform().getTransform());
			//Set the iterator to the parents child and continue the loop from here.
			currNode = currNode->child;
			continue;
		}
		//END: QUESTION #2//

		//QUESTION #3: DO WE HAVE SIBLINGS?! YES->LOOPS, NO->QUESTION_#4//
		//We dont have any kids but we might have a brother.  If we do then they may also be in need of an update from the relationship with our parent.  In this case we can move right toward the sibling since we know that we have no children to be responsible for.
		if (currNode->next != nullptr) {
			currNode = currNode->next;
			continue;
		}
		//END: QUESTION #3//

		//Thoughts//
			//If we dont have any siblings and we also dont have any children then we are at the end of a branch.  In this case we need to start moving back up the tree.  Thus begins a loop of questioning that is recursive since we could be indirectly related to the root infinitely.
			//If were at the end of the branch we dont need to be linked to our parent anymore.  Therefore we can pop it off the stack and traverse up the tree checking if there is any path that will allow us to move right as we go up.

		//QUESTION #4: DID OUR PARENT HAVE SIBLINGS?! RECURSIVE YES->LOOPS, NO->What about our grand parent? or great grand parent, or great great great great..... grand parent.
		//FUCNTION LOOPS IF ITERATOR = ROOT//
		//Create an iterator
		Tree::Leaf* itr = currNode;
		//Recursive Loop//
		while (itr != _scene->root) {
			//Does our parent have any siblings?
			if(itr->parent->next != nullptr) {
				//pop this node's parent matrix from the stack
				matrixStack.pop();
				//set the big iterator to the parent's sibling now the parent's parent matrix is on the top
				currNode = itr->parent->next;
				break;
			}
			//The parent didnt have siblings, so just pop the stack and check if the grand parent had any
			matrixStack.pop();
			itr = itr->parent;
		}
		//Will do noething if loops isnt called
		currNode = itr;
		//We made it through the while loop and it triggered the condition, therefore our little iterator is now set to the root node
		//This means we have finished updating the tree so simple set the big iterator a nullptr or the parent node and trigger the big loop condition.
		//We need a blocker if statment here because we cannot use the continue keyword. If we were to break the loop and continue the lower lines could never be called.  If we called continue in the if block were we set the big iterator.  It would only continue the little loop
		if(currNode == _scene->root)
			currNode = nullptr;
		//END:QUESTION #4://
	}
}

