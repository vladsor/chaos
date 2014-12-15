/**
 * @brief		Number of IRQ controllers.
 */
#define NUMBER_OF_IRQ_CONTROLLERS \
                        (2)

/**
 * @brief		Number of IRQ channels per controller.
 */
#define NUMBER_OF_IRQ_CHANNELS_PER_CONTROLLER \
                        (8)

/**
 * @brief		Total number of IRQ channels.
 */
#define NUMBER_OF_IRQ_CHANNELS \
                        (NUMBER_OF_IRQ_CONTROLLERS * \
                        NUMBER_OF_IRQ_CHANNELS_PER_CONTROLLER)  

#define IRQ_CHANNEL_TIMER \
                        (0)
                        
#define IRQ_CHANNEL_CASCADE \
                        (2)

