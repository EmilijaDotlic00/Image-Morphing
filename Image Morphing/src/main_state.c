#include <main_state.h>
#include <glad/glad.h>
#include <math.h>

#include <rafgl.h>

typedef struct Vec2D{
    float x;
    float y;
}Vec2D;

typedef struct Line{
    Vec2D start;
    Vec2D end;
    Vec2D vector;
    struct Line* next;
}Line;

typedef struct TransformResult{
    Vec2D u;
    Vec2D v;
    Vec2D X_source;
}TransformResult;

//prazne liste
Line* sourceLines = NULL;
Line* destLines = NULL;
Line* interLines = NULL;

int sizeOfLists = 42;

Line* head_source;
Line* head_dest;
Line* head_inter;

static int w, h;
static rafgl_raster_t raster, source, dest, image1, image2, source_lines, dest_lines;
static rafgl_texture_t tex;



Line* addLine(Line* head, Vec2D start, Vec2D end) {
    Line* newLine = (Line*)malloc(sizeof(Line));
    if (newLine == NULL) {
        printf("Error with malloc.\n");
        exit(1);
    }

    newLine->start.x = start.x;
    newLine->start.y = start.y;
    newLine->end.x = end.x;
    newLine->end.y = end.y;
    newLine->vector.x = end.x - start.x;
    newLine->vector.y = end.y - start.y;
    newLine->next = NULL;

    // Ako je lista prazna, postavljamo novu liniju kao glavu liste
    if (head == NULL) {
        return newLine;
    }

    // Inače, tražimo kraj liste i dodajemo novu liniju tamo
    struct Line* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newLine;

    return head;
}

void freeListOfLines(Line* head) {
    while (head != NULL) {
        Line* curr = head;
        head = head->next;
        free(curr);
    }
}

Line* makeSourceList(){
    // Dodavanje linija u listu
    sourceLines = addLine(sourceLines, (Vec2D){116,165}, (Vec2D){93,130});
    sourceLines = addLine(sourceLines, (Vec2D){91,130}, (Vec2D){91,115});
    sourceLines = addLine(sourceLines, (Vec2D){89,117}, (Vec2D){77,102});
    sourceLines = addLine(sourceLines, (Vec2D){76,102}, (Vec2D){79,82});
    sourceLines = addLine(sourceLines, (Vec2D){117,165}, (Vec2D){136,166});
    sourceLines = addLine(sourceLines, (Vec2D){137,164}, (Vec2D){161,134});
    sourceLines = addLine(sourceLines, (Vec2D){161,132}, (Vec2D){164,120});
    sourceLines = addLine(sourceLines, (Vec2D){164,119}, (Vec2D){174,107});
    sourceLines = addLine(sourceLines, (Vec2D){174,104}, (Vec2D){173,82});
    sourceLines = addLine(sourceLines, (Vec2D){82,80}, (Vec2D){71,58});
    sourceLines = addLine(sourceLines, (Vec2D){72,57}, (Vec2D){84,30});
    sourceLines = addLine(sourceLines, (Vec2D){87,30}, (Vec2D){119,14});
    sourceLines = addLine(sourceLines, (Vec2D){122,15}, (Vec2D){167,23});
    sourceLines = addLine(sourceLines, (Vec2D){168,23}, (Vec2D){182,53});
    sourceLines = addLine(sourceLines, (Vec2D){184,56}, (Vec2D){175,80});
    sourceLines = addLine(sourceLines, (Vec2D){9,199}, (Vec2D){41,174});
    sourceLines = addLine(sourceLines, (Vec2D){44,172}, (Vec2D){88,155});
    sourceLines = addLine(sourceLines, (Vec2D){43,181}, (Vec2D){87,193});
    sourceLines = addLine(sourceLines, (Vec2D){231,196}, (Vec2D){196,172});
    sourceLines = addLine(sourceLines, (Vec2D){193,172}, (Vec2D){157,160});
    sourceLines = addLine(sourceLines, (Vec2D){91,87}, (Vec2D){98,63});
    sourceLines = addLine(sourceLines, (Vec2D){94,92}, (Vec2D){102,84});
    sourceLines = addLine(sourceLines, (Vec2D){105,84}, (Vec2D){123,88});
    sourceLines = addLine(sourceLines, (Vec2D){139,88}, (Vec2D){157,86});
    sourceLines = addLine(sourceLines, (Vec2D){158,87}, (Vec2D){165,98});
    sourceLines = addLine(sourceLines, (Vec2D){101,97}, (Vec2D){116,100});
    sourceLines = addLine(sourceLines, (Vec2D){137,98}, (Vec2D){156,101});
    sourceLines = addLine(sourceLines, (Vec2D){104,91}, (Vec2D){116,91});
    sourceLines = addLine(sourceLines, (Vec2D){139,92}, (Vec2D){158,93});
    sourceLines = addLine(sourceLines, (Vec2D){129,93}, (Vec2D){129,119});
    sourceLines = addLine(sourceLines, (Vec2D){121,105}, (Vec2D){109,124});
    sourceLines = addLine(sourceLines, (Vec2D){137,104}, (Vec2D){150,126});
    sourceLines = addLine(sourceLines, (Vec2D){111,128}, (Vec2D){142,129});
    sourceLines = addLine(sourceLines, (Vec2D){111,133}, (Vec2D){123,148});
    sourceLines = addLine(sourceLines, (Vec2D){130,148}, (Vec2D){146,132});
    sourceLines = addLine(sourceLines, (Vec2D){154,194}, (Vec2D){156,167});
    sourceLines = addLine(sourceLines, (Vec2D){3,198}, (Vec2D){4,2});
    sourceLines = addLine(sourceLines, (Vec2D){12,5}, (Vec2D){251,5});
    sourceLines = addLine(sourceLines, (Vec2D){247,14}, (Vec2D){250,197});
    sourceLines = addLine(sourceLines, (Vec2D){96,56}, (Vec2D){120,49});
    sourceLines = addLine(sourceLines, (Vec2D){128,49}, (Vec2D){153,51});
    sourceLines = addLine(sourceLines, (Vec2D){160,57}, (Vec2D){164,80});

    return sourceLines;
}

Line* makeDestList(){
    destLines = addLine(destLines, (Vec2D){123,168}, (Vec2D){104,131});
    destLines = addLine(destLines, (Vec2D){103,128}, (Vec2D){100,112});
    destLines = addLine(destLines, (Vec2D){98,110}, (Vec2D){93,101});
    destLines = addLine(destLines, (Vec2D){93,100}, (Vec2D){94,89});
    destLines = addLine(destLines, (Vec2D){125,167}, (Vec2D){141,169});
    destLines = addLine(destLines, (Vec2D){142,168}, (Vec2D){164,141});
    destLines = addLine(destLines, (Vec2D){165,140}, (Vec2D){175,111});
    destLines = addLine(destLines, (Vec2D){175,110}, (Vec2D){182,92});
    destLines = addLine(destLines, (Vec2D){181,91}, (Vec2D){181,79});
    destLines = addLine(destLines, (Vec2D){94,86}, (Vec2D){95,60});
    destLines = addLine(destLines, (Vec2D){96,59}, (Vec2D){109,34});
    destLines = addLine(destLines, (Vec2D){111,33}, (Vec2D){140,23});
    destLines = addLine(destLines, (Vec2D){142,25}, (Vec2D){170,39});
    destLines = addLine(destLines, (Vec2D){171,41}, (Vec2D){178,61});
    destLines = addLine(destLines, (Vec2D){180,63}, (Vec2D){181,77});
    destLines = addLine(destLines, (Vec2D){27,198}, (Vec2D){51,171});
    destLines = addLine(destLines, (Vec2D){51,171}, (Vec2D){100,147});
    destLines = addLine(destLines, (Vec2D){64,172}, (Vec2D){111,183});
    destLines = addLine(destLines, (Vec2D){211,196}, (Vec2D){205,166});
    destLines = addLine(destLines, (Vec2D){203,167}, (Vec2D){162,159});
    destLines = addLine(destLines, (Vec2D){100,88}, (Vec2D){110,64});
    destLines = addLine(destLines, (Vec2D){105,87}, (Vec2D){110,79});
    destLines = addLine(destLines, (Vec2D){112,80}, (Vec2D){128,84});
    destLines = addLine(destLines, (Vec2D){146,84}, (Vec2D){164,82});
    destLines = addLine(destLines, (Vec2D){166,84}, (Vec2D){173,94});
    destLines = addLine(destLines, (Vec2D){106,99}, (Vec2D){120,104});
    destLines = addLine(destLines, (Vec2D){145,102}, (Vec2D){166,102});
    destLines = addLine(destLines, (Vec2D){110,94}, (Vec2D){126,95});
    destLines = addLine(destLines, (Vec2D){147,96}, (Vec2D){164,96});
    destLines = addLine(destLines, (Vec2D){136,93}, (Vec2D){136,124});
    destLines = addLine(destLines, (Vec2D){129,109}, (Vec2D){114,129});
    destLines = addLine(destLines, (Vec2D){143,110}, (Vec2D){159,130});
    destLines = addLine(destLines, (Vec2D){124,130}, (Vec2D){151,130});
    destLines = addLine(destLines, (Vec2D){120,138}, (Vec2D){128,156});
    destLines = addLine(destLines, (Vec2D){140,156}, (Vec2D){155,135});
    destLines = addLine(destLines, (Vec2D){145,195}, (Vec2D){158,162});
    destLines = addLine(destLines, (Vec2D){3,198}, (Vec2D){4,2});
    destLines = addLine(destLines, (Vec2D){12,5}, (Vec2D){251,5});
    destLines = addLine(destLines, (Vec2D){247,14}, (Vec2D){250,197});
    destLines = addLine(destLines, (Vec2D){116,59}, (Vec2D){130,46});
    destLines = addLine(destLines, (Vec2D){135,48}, (Vec2D){155,53});
    destLines = addLine(destLines, (Vec2D){156,57}, (Vec2D){167,76});

    return destLines;
}

// interpolacija linija
Line* line_interpolation(Line* head_source, Line* head_dest, float t) {

    Line* curr_source = head_source;
    Line* curr_dest = head_dest;

    freeListOfLines(interLines);
    interLines = NULL;

    while (curr_source != NULL) {
        Vec2D start, end;
        start.x = (1 - t) * curr_source->start.x + t * curr_dest->start.x;
        start.y = (1 - t) * curr_source->start.y + t * curr_dest->start.y;
        end.x = (1 - t) * curr_source->end.x + t * curr_dest->end.x;
        end.y = (1 - t) * curr_source->end.y + t * curr_dest->end.y;

        interLines = addLine(interLines, start, end);
        curr_source = curr_source->next;
        curr_dest = curr_dest->next;
    }
    head_inter = interLines;
    return head_inter;
}

// Definisanje source i dest linije u slucaju rada sa jednim parom linija
//za testiranje

//Line sourceLine = { {100, 94}, {155, 97} };
//Line destLine = { {110, 99}, {165, 99} };

Vec2D perpendicular(Vec2D vec) {
    Vec2D perpendicular;
    perpendicular.x = -vec.y;
    perpendicular.y = vec.x;
    return perpendicular;
}

Vec2D addVecs(Vec2D vector1, Vec2D vector2) {
    Vec2D result;
    result.x = vector1.x + vector2.x;
    result.y = vector1.y + vector2.y;
    return result;
}

Vec2D subtractVecs(Vec2D vector1, Vec2D vector2) {
    Vec2D result;
    result.x = vector1.x - vector2.x;
    result.y = vector1.y - vector2.y;
    return result;
}

Vec2D multiplyVecs(Vec2D vector1, Vec2D vector2) {
    Vec2D result;
    result.x = vector1.x * vector2.x;
    result.y = vector1.y * vector2.y;
    return result;
}

Vec2D divideVecByScalar(Vec2D vector, float scalar) {
    Vec2D result;

    if(scalar == 0){
        printf("Deljenje nulom, skalar ima vrednost 0");
        result.x = 0;
        result.y = 0;
        return result;
    }

    // Deljenje svake komponente vektora skalarnom vrednošću
    result.x = 1.0f*vector.x / scalar;
    result.y = 1.0f*vector.y / scalar;

    return result;
}

float intensityVec(Vec2D vector) {
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}

TransformResult transformPoint(Vec2D X_dest, Line sourceLine, Line destLine) {

    Vec2D P_dest = destLine.start;
    Vec2D Q_dest = destLine.end;

    Vec2D P_source = sourceLine.start;
    Vec2D Q_source = sourceLine.end;

    Vec2D PX_dest = subtractVecs(X_dest, P_dest);
    Vec2D PQ_dest = subtractVecs(Q_dest, P_dest);


    float intensityVecPQ_dest = intensityVec(subtractVecs(Q_dest, P_dest));

    Vec2D above_u = multiplyVecs(PX_dest, PQ_dest);
    float below_u = pow(intensityVecPQ_dest, 2);


    Vec2D u = divideVecByScalar(above_u, below_u);

    Vec2D above_v= multiplyVecs(PX_dest, perpendicular(PQ_dest));
    float below_v = intensityVecPQ_dest;

    Vec2D v = divideVecByScalar(above_v, below_v);

    Vec2D PQ_source = subtractVecs(Q_source, P_source);
    Vec2D firstPart_X_source = addVecs(P_source, multiplyVecs(u,PQ_source));
    Vec2D secondPart_X_source = divideVecByScalar(multiplyVecs(v, perpendicular(PQ_source)), intensityVec(PQ_source));

    Vec2D X_source = addVecs(firstPart_X_source, secondPart_X_source);

    TransformResult result;
    result.u = u;
    result.v = v;
    result.X_source = X_source;

    return result;
}

Vec2D beierNeelyTransform(Vec2D X, Line* curr_sourceLine, Line* curr_destLine, float a, float b, float p){

    Vec2D DSUM = {0, 0};
    float weightsum = 0;

    Line sourceLine;
    Line destLine;

    Vec2D u;
    Vec2D v;
    Vec2D X_source;

    float dist;
    float weight;
    float length;

    while (curr_sourceLine != NULL) {

        sourceLine.start = curr_sourceLine->start;
        sourceLine.end = curr_sourceLine->end;

        destLine.start = curr_destLine->start;
        destLine.end = curr_destLine->end;

        //transformacija za jednu liniju (u,v,X_source)
        TransformResult result = transformPoint(X, sourceLine, destLine);
        u = result.u;
        v = result.v;
        X_source = result.X_source;

        Vec2D Di = subtractVecs(X_source, X);

        dist = abs(intensityVec(v));

        if(intensityVec(u)<0)
            dist = rafgl_distance2D(X.x, X.y, destLine.start.x, destLine.start.y);
        if(intensityVec(u)>1)
            dist = rafgl_distance2D(X.x, X.y, destLine.end.x, destLine.end.y);

        length = rafgl_distance2D(destLine.start.x, destLine.start.y, destLine.end.x, destLine.end.y);
        weight = pow(pow(length, p) / (a + dist), b);

        // Update DSUM, weightsum
        DSUM.x += Di.x * weight;
        DSUM.y += Di.y * weight;
        weightsum += weight;
        curr_sourceLine = curr_sourceLine->next;
        curr_destLine = curr_destLine->next;
    }

    //X'
    Vec2D X_prime;
    X_prime.x = X.x + DSUM.x / weightsum;
    X_prime.y = X.y + DSUM.y / weightsum;

    return X_prime;
}

void main_state_init(GLFWwindow *window, void *args, int width, int height)
{
    w = width;
    h = height;
    rafgl_raster_init(&raster, w, h);

    rafgl_raster_init(&source, w, h);
    rafgl_raster_init(&dest, w, h);

    rafgl_raster_load_from_image(&image1, "res/images/image1.jpg");
    rafgl_raster_load_from_image(&image2, "res/images/image2.jpg");

    rafgl_texture_init(&tex);

    makeSourceList();
    makeDestList();

    head_source = sourceLines;
    head_dest = destLines;
    head_inter = interLines;

    rafgl_raster_load_from_image(&source_lines, "res/images/image1.jpg");
    rafgl_raster_load_from_image(&dest_lines, "res/images/image2.jpg");

    Line* current_source = sourceLines;
    Line* current_dest = destLines;
    while (current_source != NULL){

        rafgl_raster_draw_line(&source_lines, current_source->start.x, current_source->start.y, current_source->end.x, current_source->end.y, rafgl_RGB(255,255,255));

        rafgl_raster_draw_line(&dest_lines, current_dest->start.x, current_dest->start.y, current_dest->end.x, current_dest->end.y, rafgl_RGB(255,255,255));
        current_source = current_source->next;
        current_dest = current_dest->next;
    }

}

int original = 0;
int destination = 0;
int original_with_lines = 0;
int destination_with_lines = 0;

int c=0;

int frames=10;

void main_state_update(GLFWwindow *window, float delta_time, rafgl_game_data_t *game_data, void *args)
{

    if(game_data->keys_down[RAFGL_KEY_1])
        original=1;
    else
        original=0;
    if(game_data->keys_down[RAFGL_KEY_2])
        destination=1;
    else
        destination=0;
    if(game_data->keys_down[RAFGL_KEY_3])
        original_with_lines=1;
    else
        original_with_lines=0;
    if(game_data->keys_down[RAFGL_KEY_4])
        destination_with_lines=1;
    else
        destination_with_lines=0;
    if(game_data->keys_down[RAFGL_KEY_5])
        c=0;
    rafgl_pixel_rgb_t sampled_source, sampled_dest, result;

    int x, y;
    int u,v;

    float a, b, p;

    //setovanje parametara
    a=0.1;
    b=1.25;
    p=1;

    float xn, yn;

    float t = (float)c / frames;

    if(t>1){

        for(y = 0; y < h; y++)
        {
            for(x = 0; x < w; x++)
            {
                pixel_at_m(raster, x, y) = pixel_at_m(image2, x, y);
            }
        }
        return 0;
    }

    printf("%d/%d frame, t = %f\n", c, frames, t);

    c++;

    head_inter = line_interpolation(head_source, head_dest,  t);
    Line* curr = head_inter;

    for(y = 0; y < h; y++)
    {
        yn = 1.0f*y/h;
        for(x = 0; x < w; x++)
        {
            xn = 1.0f*x/w;

            Vec2D point = {x,y};

            Vec2D newPoint_source = beierNeelyTransform(point, sourceLines, interLines, a, b, p);
            if(newPoint_source.x<0 || newPoint_source.x>w-1 || newPoint_source.y<0 || newPoint_source.y>h-1){
                sampled_source = rafgl_bilinear_sample(&image1, xn, yn);

            }else{
                sampled_source = pixel_at_m(image1, (int)newPoint_source.x, (int)newPoint_source.y);
            }
            pixel_at_m(source, x, y) = sampled_source;

            Vec2D newPoint_dest = beierNeelyTransform(point, destLines, interLines, a, b, p);
            if(newPoint_dest.x<0 || newPoint_dest.x>w-1 || newPoint_dest.y<0 || newPoint_dest.y>h-1){
                sampled_dest = rafgl_bilinear_sample(&image2, xn, yn);

            }else{
                sampled_dest = pixel_at_m(image2, (int)newPoint_dest.x, (int)newPoint_dest.y);
            }
            pixel_at_m(dest, x, y) = sampled_dest;

            sampled_source = pixel_at_m(source,x,y);
            sampled_dest = pixel_at_m(dest,x,y);

            result.r = (1-t)*sampled_source.r + t*sampled_dest.r;
            result.g = (1-t)*sampled_source.g + t*sampled_dest.g;
            result.b = (1-t)*sampled_source.b + t*sampled_dest.b;

            pixel_at_m(raster, x, y) = result;
        }
    }
}

void main_state_render(GLFWwindow *window, void *args)
{

    if(original==1)
        rafgl_texture_load_from_raster(&tex, &image1);
    else if(destination==1)
        rafgl_texture_load_from_raster(&tex, &image2);
    else if(original_with_lines==1)
        rafgl_texture_load_from_raster(&tex, &source_lines);
    else if(destination_with_lines==1)
        rafgl_texture_load_from_raster(&tex, &dest_lines);
    else
        rafgl_texture_load_from_raster(&tex, &raster);

    rafgl_texture_show(&tex, 0);
}

void main_state_cleanup(GLFWwindow *window, void *args)
{
    freeListOfLines(sourceLines);
    freeListOfLines(destLines);
    rafgl_raster_cleanup(&raster);
    rafgl_raster_cleanup(&image1);
    rafgl_raster_cleanup(&image2);
    rafgl_raster_cleanup(&source);
    rafgl_raster_cleanup(&dest);
    rafgl_raster_cleanup(&source_lines);
    rafgl_raster_cleanup(&dest_lines);
}
