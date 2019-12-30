#ifndef _DECORATOR_H_
#define _DECORATOR_H_
#include "AbsBoard.h"
#include <memory>

//Decorator class that has a pointer to our Abstract Board class
class Decorator: public AbsBoard {
        protected:
		std::shared_ptr<AbsBoard> absboard;
        public:
                Decorator(std::shared_ptr<AbsBoard> absboard);
                void apply(Board &b) override;
                virtual ~Decorator();
};

#endif
