#ifndef __ImplInputHandler_hpp__
#define __ImplInputHandler_hpp__
#include <vector>
#include <utility>
#include <functional>

namespace Handler
{
	enum mouse_buttons
	{
		LEFT = 0,
		MIDDLE = 1,
		RIGHT = 2
	};

	template<int BUTTON>
	struct button_mask
	{
		const static int value = 0;
	};

	template<>
	struct button_mask<RIGHT>
	{
		const static int value = SDL_BUTTON_RMASK;
	};

	template<>
	struct button_mask<MIDDLE>
	{
		const static int value = SDL_BUTTON_MMASK;
	};

	template<>
	struct button_mask<LEFT>
	{
		const static int value = SDL_BUTTON_LMASK;
	};




	class MouseInput
	{
		public:
		std::vector<bool> m_mouseButtonStates{false,false,false};

		std::vector<std::pair<int,int> > m_mouseButtonPos
		{/* Button Down */
			std::pair<int,int>{-1,-1}, /* LEFT */
			std::pair<int,int>{-1,-1}, /* MIDDLE */
			std::pair<int,int>{-1,-1},  /* RIGHT */
			/* Button Up */
			std::pair<int,int>{-1,-1}, /* LEFT */
			std::pair<int,int>{-1,-1}, /* MIDDLE */
			std::pair<int,int>{-1,-1},  /* RIGHT */

		};

		template<int BUTTON, int DEPRESSED_STATE>
		std::pair<int,int> const & getMousePosition() const 
		{ 
			int offset = (DEPRESSED_STATE & 0xFF01) ? 0 : (DEPRESSED_STATE & 0xFF02) ? 3 : -1;

			assert(offset >= 0);
			offset += BUTTON;
			return m_mouseButtonPos[offset];
		}

		template<int BUTTON> /* mouse event position helper func */
		void update_pos(SDL_Event const& event, bool btn_state)
		{
			if(m_mouseButtonStates[BUTTON] != btn_state)
			{
				m_mouseButtonPos[(btn_state ? 0 : 3) + BUTTON] = std::pair<int,int>(event.button.x,event.button.y);
				m_mouseButtonStates[BUTTON] = btn_state;
			}

		}

		template<int BUTTON>
		void mouse_update_buttons_state(Uint32 &b_mask,SDL_Event const &event)
		{
			const bool btn_state = m_mouseButtonStates[BUTTON];
			const bool eval_state = (bool)(b_mask & button_mask<BUTTON>::value);
			if(btn_state != eval_state)
			{
				update_pos<BUTTON>(event,!btn_state);

				/*if(!btn_state)
					update_pos<BUTTON,true>(event);
				else
					update_pos<BUTTON,false>(event);
*/
				m_mouseButtonStates[BUTTON] = eval_state;
			}
		
		}


	
	};



};

#endif

