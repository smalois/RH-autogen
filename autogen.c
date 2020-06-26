#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DL	0x100
#define L	0x80
#define UL	0x40
#define D	0x20
#define C	0x10
#define U	0x8
#define UR	0x4
#define R	0x2
#define DR	0x1

#define num_panels 9
#define num_possible_states 18

enum step_state { Ldl, Ll, Lul, Ld, Lc, Lu, Lur, Lr, Ldr, 
		  Rdl, Rl, Rul, Rd, Rc, Ru, Rur, Rr, Rdr };

struct step_style {
	unsigned short possible_next_step[num_possible_states];
	enum step_state history[2];
	void (*rules[2])(enum step_state[], enum step_state[], int*);
};

void rule_no_repeats(const enum step_state *history_buffer, enum step_state *possible_panels, int *pp_count) {
	_Bool found_repeat = 0;
	for (int i = 0; i < *pp_count; ++i) {
		if (found_repeat) {
			possible_panels[i-1] = possible_panels[i];
		}
		if (possible_panels[i] = history_buffer[1]) {
			*pp_count--;
			found_repeat = 1;
		}
	}
}

void rule_no_big_step(enum step_state *history_buffer, enum step_state *possible_panels, int *pp_count) {

}

_Bool is_left_foot(enum step_state state) {
	return state <= Ldr;
}

enum step_state get_random_next_step(enum step_state cur_step, struct step_style style) {
	unsigned const int next_step_bits = style.possible_next_step[cur_step];
	unsigned const int mask = 0x100;

	enum step_state possible_panels[num_panels];
	unsigned int num_possible_next_panels = 0;

	for (unsigned int i = 0; i < num_panels; ++i) {
		if (next_step_bits & (mask >> i)) {
			possible_panels[num_possible_next_panels++] = 
				i + (is_left_foot(cur_step) * num_panels); 
		}
	}

//	rule_no_repeats(style.history, possible_panels, &num_possible_next_panels);

	return possible_panels[rand() % num_possible_next_panels];
}

void print_step(enum step_state cur_step) {
	char note_bar[10] = "---------";
	char keymap[10] = "zaqxswedc";

	if (is_left_foot(cur_step)) {
		note_bar[cur_step] = 'L';
	} else {
		note_bar[cur_step % num_panels] = 'R';
	}

	printf("%c\n", keymap[cur_step % num_panels]);
//	printf("%s\n", note_bar);
}

void initialize_easy_steps(struct step_style *style) {
	style->possible_next_step[Ldl] = C | R | D | DR;
	style->possible_next_step[Ll] = U | UR | C | R | D | DR;
	style->possible_next_step[Lul] = U | UR | C | R;
	style->possible_next_step[Ld] = R | DR | U;
	style->possible_next_step[Lc] = UR | R | DR;
	style->possible_next_step[Lu] = UR | R | D;
	style->possible_next_step[Rd] = DL | L | U;
	style->possible_next_step[Rc] = UL | L | DL;
	style->possible_next_step[Ru] = UL | L | D;
	style->possible_next_step[Rur] = UL | U | L | C;
	style->possible_next_step[Rr] = UL | U | L | C | DL | D;
	style->possible_next_step[Rdr] = L | C | DL | D;
	style->rules[0] = rule_no_repeats;
}
 
int main(int argc, char** argv) {
	unsigned int steps_to_generate = 0; 
	enum step_state current_step = Rr;

	struct step_style style;
	initialize_easy_steps(&style);

	if (argc != 2) {
		puts("Usage: ./autogen <number of steps to generate>");
		exit(0);
	}

	steps_to_generate = atoi(argv[1]);

	srand(time(0));
	for (int i = 0; i < steps_to_generate; ++i) {
		print_step(current_step);
		current_step = get_random_next_step(current_step, style);
	}

	return 0;
}
