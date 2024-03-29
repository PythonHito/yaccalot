#ifndef __EXPRESSION_H__
#define __EXPRESSION_H__

/**
 * @brief The operation type
 */
typedef enum tagEOperationType
{
    eINVERT,
    eCAPITALISE,
    eVALUE
} EOperationType;

/**
 * @brief The expression structure
 */
typedef struct tagSExpression
{
    EOperationType type; /* /< type of operation */

    char* value; /* /< valid only when type is eVALUE */
    struct tagSExpression *left; /* /<  left side of the tree */
    struct tagSExpression *right; /* /< right side of the tree */
} SExpression;

/**
 * @brief It creates an identifier
 * @param value The number value
 * @return The expression or NULL in case of no memory
 */
SExpression *createString(char* value);

SExpression *createUnaryOperation(EOperationType type, SExpression *left);

/**
 * @brief It creates an operation
 * @param type The operation type
 * @param left The left operand
 * @param right The right operand
 * @return The expression or NULL in case of no memory
 */
SExpression *createOperation(EOperationType type, SExpression *left, SExpression *right);

/**
 * @brief Deletes a expression
 * @param b The expression
 */
void deleteExpression(SExpression *b);

#endif /* __EXPRESSION_H__ */
