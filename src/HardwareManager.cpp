
#include "HardwareManager.h"


const float HardwareManager::WHEEL_RPM_FULL_SPEED = 0.0;
const float HardwareManager::WHEEL_RADIUS = 0.0;

HardwareManager::HardwareManager(JoystickManagerManager* jman):
    BaseManager(),
    m_finished(false),
    m_talons(),
    m_servos()
{
    m_drive = NULL;
    m_jman = jman;
}

HardwareManager::~HardwareManager(){
}

int HardwareManager::Init(){
    log_info("Beginning HardwareManager Initialization.");
    //this->addTalon(0,"frontLeft");
    log_info("Adding CANTalon frontLeft at ID=0");
    this->m_talons["frontLeft"] = new CANTalon(0);
    log_info("Adding CANTalon backLeft at ID=1");
    this->m_talons["backLeft"] = new CANTalon(1);
    log_info("Adding CANTalon frontRight at ID=2");
    this->m_talons["frontRight"] = new CANTalon(2);
    log_info("Adding CANTalon backRight at ID=3");
    this->m_talons["backRight"] = new CANTalon(3);
    log_info("Adding CANTalon intake at ID=4");
    this->m_talons["intake"] = new CANTalon(4);
    
    log_info("Adding Talon leftShoot at ID=9");
    this->m_talons["leftShoot"] = new Talon(9);
    log_info("Adding Talon rightShoot at ID=8");
    this->m_talons["rightShoot"] = new Talon(8);

    log_info("Adding Talon TESTTALON at ID=3");
    this->m_talons["TESTTALON"] = new Talon(1);

    log_info("Adding Talon ArmRaiseMotor at ID=4");
    this->m_talons["ArmRaiseMotor"] = new Talon(1);

    log_info("Adding Talon ArmExtendMotor at ID=4");
    this->m_talons["ArmExtendMotor"] = new Talon(1);

    log_info("Registering Servos.");
    log_info("Adding Servo TESTSERVO at ID=0");
    this->m_servos["TESTSERVO"] = new Servo(0);

    log_info("Adding Servo WinchActive at ID=1");
    this->m_servos["WinchActivate"] = new Servo(5);

    log_info("Adding Servo IntakeArmActivate at ID=2");
    this->m_servos["IntakeArmActivate"] = new Servo(6);

    log_info("Adding Servo flap thing at ID=3");
    this->m_servos["flap thing"] = new Servo(7);

    log_info("Constructing RobotDrive");
    m_drive = new RobotDrive(
            this->m_talons["frontLeft"],this->m_talons["backLeft"],
            this->m_talons["frontRight"],this->m_talons["backRight"]);

    log_info("Setting default Servo values to 0.");
    this->m_servos["TESTSERVO"]->SetAngle(0);
    this->m_servos["WinchActivate"]->SetAngle(0);

    log_info("Done Initializing HardwareManager.");
    return 0;
}

int HardwareManager::Update(){
    int ret = 0;
    ret |= this->move();
    ret |= this->launch();
    ret |= this->suck();
    ret |= this->climb();
    return ret;
}

bool HardwareManager::IsFinished(){
    return this->m_finished;
}

int HardwareManager::End(){
    return 0;
}

int HardwareManager::move(){
    log_warn("WARNING! I have removed all driving functionality while we rework Joystick Manager to hold two joysticks.");
    log_warn("Actually, I've re-enabled it, but I'm not sure if it works yet. Let's just assume it does for now.");
    this->m_drive->TankDrive(m_jman->getJoystickManager(0)->GetJoystickX(),m_jman->getJoystickManager(1)->GetJoystickX());
    return 0;
}

int HardwareManager::launch(){
    if(m_jman->getJoystickManager(1)->GetButtonByIndex(1)->Get()){//HardwareManager::HW_LAUNCH_BUTTON_IDX)){
        this->m_talons["leftShoot"]->Set(1);
        this->m_talons["rightShoot"]->Set(1);
        this->m_servos["flap thing"]->Set(360);
    }else{
        // Move the launchers backwards constantly to keep the ball from falling out
        // NOTE: May be too strong of a speed (maybe 10%?)
        this->m_talons["leftShoot"]->Set(-0.2);
        this->m_talons["rightShoot"]->Set(-0.2);
        this->m_servos["flap thing"]->Set(0);
    }
    return 0;
}

int HardwareManager::release(){
    if(m_jman->getJoystickManager(2)->Get(HardwareManager::HW_RELEASE_BUTTON_IDX)){
        this->m_talons["leftShoot"]->Set(0.2);
        this->m_talons["rightShoot"]->Set(0.2);
        this->m_servos["flap thing"]->Set(360);
        // Also, should it be before or after the motors start up?
    }else{
        this->m_servos["flap thing"]->Set(0);
    }
    return 0;
}

int HardwareManager::init_climb(){
    this->m_servos["WinchActivate"]->SetAngle(360);
    return 0;
}

int HardwareManager::init_suck(){
    this->m_servos["IntakeArmActivate"]->SetAngle(360);
    return 0;
}

int HardwareManager::uninit_suck(){
    this->m_servos["IntakeArmActivate"]->SetAngle(0);
    return 0;
}

int HardwareManager::suck(){
    // TODO: Add pre-suck and post-suck stuff
    // Actually, is there anything it init and post init?
    if(m_jman->getJoystickManager(2)->Get(HardwareManager::HW_SUCK_BUTTON_IDX)){
        this->m_talons["intake"]->Set(1);
    }
    return 0;
}

int HardwareManager::climb(){
    if(m_jman->getJoystickManager(2)->Get(HardwareManager::HW_CLIMB_BUTTON_IDX)){
        if(this->m_servos["WinchActivate"]->GetAngle() == 360)
            this->m_talons["ArmExtendMotor"]->Set(-1);
        else
            this->init_climb();
    }
    return 0;
}

// The arm is moved by that arcade stick thing that is basically buttons rather than axes
int HardwareManager::move_arm(){
    if(m_jman->getJoystickManager(3)->Get(HardwareManager::HW_RAISE_BUTTON_IDX))
        this->m_talons["ArmRaiseMotor"]->Set(1);
    else if(m_jman->getJoystickManager(3)->Get(HardwareManager::HW_RAISE_BUTTON_IDX+1))
        this->m_talons["ArmRaiseMotor"]->Set(-1);

    if(m_jman->getJoystickManager(3)->Get(HardwareManager::HW_EXTEND_BUTTON_IDX))
        this->m_talons["ArmExtendMotor"]->Set(1);
    else if(m_jman->getJoystickManager(3)->Get(HardwareManager::HW_EXTEND_BUTTON_IDX+1))
        this->m_talons["ArmExtendMotor"]->Set(-1);

    return 0;
}

int HardwareManager::stop_suck(){
    // TODO: Somehow get the button thing here
    // Is it Digital IO, Analog, or something else
    if(false){
        this->m_talons["intake"]->Set(0);
    }
    return 0;
}

