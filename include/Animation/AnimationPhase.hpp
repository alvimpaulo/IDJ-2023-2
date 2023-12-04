class AnimationPhase
{
public:
    enum class Phase : int{
        Idle,
        Run,
        LoadAttack,
        Critical,
        Resting,
        RunBack,
    };
    AnimationPhase(Phase phase);
    Phase phase;
    
};
