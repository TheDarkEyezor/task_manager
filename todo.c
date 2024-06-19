
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <leif/leif.h>
#include <stdint.h>
#include <string.h>

#include "config.h"


#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_MARGIN 20.0f
#define TITLE_SIZE 40
#define BUTTON_WIDTH 160.0f
#define NUM_FILTERS = 6
#define ADD_TASK_BUTTON_COLOUR {76, 187, 23, 255}

static LfFont titleFont;
typedef enum {ALL, IN_PROGRESS, COMPLETED, LOW, MEDIUM, HIGH} entryFilter; 
static entryFilter currentFilter;

static void renderTopBar() {
    // Sets the font for all the text below this point
        lf_push_font(&titleFont);
        lf_text("Your Todos");
        lf_pop_font();

        // Defines a new scope in which the button will be defined
        {
            // Creates a new fixed button called "New Task" and defines its padding
            LfUIElementProps props = lf_get_theme().button_props;
            props.margin_left = props.margin_right = 0.0f;
            props.color = (LfColor) ADD_TASK_BUTTON_COLOUR; // Kelly Green colour
            props.border_width = 0.0f;
            props.corner_radius = 4.0f;
            lf_push_style_props(props);

            // Sets the x-axis position where the next element will be inserted in the div
            lf_set_ptr_x_absolute(WINDOW_WIDTH - BUTTON_WIDTH - (WINDOW_MARGIN * 2));
            // lf_set_line_should_overflow(false);

            lf_button_fixed("New Task", BUTTON_WIDTH, -1);
            lf_pop_style_props();
        }
}

int main() {
    glfwInit();

    // Creating the GUI window 
    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Task Manager", NULL, NULL);
    glfwMakeContextCurrent(window);

    lf_init_glfw(WINDOW_WIDTH, WINDOW_HEIGHT, window);

    // Makes every div defined within the window transparent (no colour of its own)
    LfTheme theme = lf_get_theme();
    theme.div_props.color = LF_NO_COLOR;
    lf_set_theme(theme);

    titleFont = lf_load_font("./fontfiles/inter-bold.ttf", TITLE_SIZE);

    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);

        lf_begin();

        // Defines the div wherein the todo app will exist, by defining window margins
        lf_div_begin(((vec2s){WINDOW_MARGIN, WINDOW_MARGIN}), 
                     ((vec2s){WINDOW_WIDTH - (2 * WINDOW_MARGIN), WINDOW_HEIGHT - (2 * WINDOW_MARGIN)}),
                     true // Makes the window scrollable
                    );

        renderTopBar(); // Renders the top bar (containing title and 'add new task' button)
        lf_next_line(); // Moves to the next line in the div
        // {

        //     static const char *filters[] = {"ALL", "IN PROGRESS", "LOW", "MEDIUM", "HIGH"};

        //     LfUIElementProps props = lf_get_theme().button_props;
        //     props.margin_left = 10.0f;
        //     props.margin_right = 10.0f;
        //     props.margin_top = 20.0f;
        //     props.padding = 10.0f;
        //     props.border_width = 0.0f;
        //     props.color = LF_NO_COLOR;
        //     props.corner_radius = 8.0f;
        //     props.text_color = LF_WHITE;
            
        //     // Sets the UI of buttons to make them appear just as plain text
        //     LfUIElementProps props = lf_get_theme().text_props;
        //     props.margin_right = 30.0f;
        //     props.margin_top = 30.0f;
        //     lf_push_style_props(props);
        //     lf_set_no_render(true);

        //     float width = 0;
        //     float prevXPtr = lf_get_ptr_x();

        //     for(int i = 0; i < **filters; i++) {
        //         lf_button(filters[i]);
        //     }
        //     lf_set_no_render(true);
        //     // Gets the width of all the filter buttons combined with their right margins
        //     width = lf_get_ptr_x() - prevXPtr - props.margin_right - props.padding; 

        //     // Sets the div cursor to point to the x-position at the start of where we wish to insert the buttons
        //     lf_set_ptr_x_absolute(WINDOW_WIDTH - width - WINDOW_MARGIN);

        //     // Inserts the buttons into the right x-axis positions in the div
        //     lf_set_line_should_overflow(false);
        //     for(int i = 0; i < **filters; i++) {
        //         lf_push_style_props(props);
        //         lf_button(filters[i]);
        //         lf_pop_style_props();
        //     }
        //     lf_set_line_should_overflow(true);
        // }

        lf_div_end();
        lf_end();

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    lf_free_font(&titleFont); // Frees the memory allocated for the title font
    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}