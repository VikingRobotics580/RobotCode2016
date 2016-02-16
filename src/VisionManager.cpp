#include "VisionManager.h"
#include "Vision/VisionAPI.h"
#include "Vision/RGBImage.h"
#include "macros.h"

VisionManager::VisionManager():
    BaseManager()
{
    m_camera = new AxisCamera(VisionManager::CAM_IP);
    m_lastPos = new int[2];
    m_currPos = new int[2];
}

VisionManager::~VisionManager(){
    // TODO: Figure out why this is throwing a warning
    delete[] m_lastPos;
    delete[] m_currPos;
}

int VisionManager::Update(){
    // Get image from camera
    RGBImage* image = new RGBImage();
    if(this->m_camera->GetImage(image)){
        log_err("Failed to get image from camera.");
        return 1;
    }

    // Mask the image (pull out vision tape)
    // TODO: Find color of vision tape so we can properly mask it
    BinaryImage* masked = image->ThresholdRGB(0,0,0,0,0,0);

    // Find most significant artifact (biggest artifact closest to the top-left corner)
    int pos[2] = {-1,-1};
    if(this->findMostSignificantArtifact((Image*)masked,pos))
        log_test("Unable to find any significant artifacts.");
    
    // Update position variables
    this->m_lastPos = this->m_currPos;
    this->m_currPos = pos;
    return 0;
}

int VisionManager::Init(){
    return 0;
}

int VisionManager::End(){
    return 0;
}

bool VisionManager::IsFinished(){
    return this->m_finished;
}

bool VisionManager::hasImageChanged(){
    return (m_lastPos[0] != m_currPos[0] || m_lastPos[1] != m_currPos[1]);
}

int* VisionManager::compareImgFrom(Image* img,int x,int y){
    int* err_succ = new int[2];
    for(int w=0; w<VisionManager::SAMPLE_WIDTH;w++){
        for(int h=0; h<VisionManager::SAMPLE_HEIGHT;h++){
            if(h < VisionManager::CAM_HEIGHT || w < VisionManager::CAM_WIDTH){
                // Generate the two points
                Point p1;
                p1.x=(w+x);
                p1.y=(h+y);

                Point p2;
                p2.x=w;
                p2.y=h;

                // Generate pixel objects
                PixelValue pixel1;
                PixelValue pixel2; 

                // NOTE: I'm taking the address of the value here, watch out for seg-faults!
                // Get the pixels at p1 and p2
                // If either throw an error, count this as a failure
                if(frcGetPixelValue(img,p1,&pixel1) || frcGetPixelValue(img,p2,&pixel2)){
                    err_succ[0]++;
                    continue;
                }
                // Only R should still be in existance
                if(pixel1.rgb.R != pixel2.rgb.R)
                    err_succ[0]++;
                else
                    err_succ[1]++;
            }else{
                err_succ[0]++;
            }
        }
    }
    return err_succ;
}

// Assume that image has already been masked and the only two colors in the entire image are solid red (255,0,0) and solid black (0,0,0)
int VisionManager::findMostSignificantArtifact(Image* image,int pos[2]){
    for(int x=0; x<VisionManager::CAM_WIDTH;x++){
        for(int y=0; y<VisionManager::CAM_HEIGHT;y++){
            // NOTE: I'm taking the address of the value here, watch out for seg-faults!
            // Attempt to get the pixel at coordinate (x,y)
            PixelValue pixel;
            Point point;
            point.x = x;
            point.y = y;
            if(frcGetPixelValue(image,point,&pixel))
                log_err("An error occurred while getting the pixel at (%d,%d)",x,y);

            // Is the pixel red?
            if(pixel.rgb.R == 255){
                int* err_succ = this->compareImgFrom(image,x,y);
                if(err_succ[0] < err_succ[1]*VisionManager::TOLERANCE_PERCENT){
                    pos[0] = x;
                    pos[1] = y;
                    return 0;
                }
            }
        }
    }
    return 1;
}

