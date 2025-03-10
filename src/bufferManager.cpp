#include "global.h"

BufferManager::BufferManager()
{
    logger.log("BufferManager::BufferManager");
}

/**
 * @brief Function called to read a page from the buffer manager. If the page is
 * not present in the pool, the page is read and then inserted into the pool.
 *
 * @param tableName 
 * @param pageIndex 
 * @return Page 
 */
Page BufferManager::getPage(string tableName, int pageIndex)
{
    logger.log("BufferManager::getPage");
    string pageName = "../data/temp/" + tableName + "_Page" + to_string(pageIndex);
    if (this->inPool(pageName))
        return this->getFromPool(pageName);
    else
        return this->insertIntoPool(tableName, pageIndex);
}

/**
 * @brief Function called to read a page from the buffer manager. If the page is
 * not present in the pool, the page is read and then inserted into the pool.
 *
 * @param matrixName 
 * @param indx
 * @param indy 
 * @return Page 
 */
Page BufferManager::getMatrixPage(string matrixName, int indx, int indy)
{
    logger.log("BufferManager::getMatrixPage");
    string pageName = "../data/temp/"+ matrixName + "_Page" + to_string(indx) + "_" + to_string(indy);
    if (this->inPool(pageName))
    {
        return this->getFromPool(pageName);
    }
    else
    {
        BLOCKS_READ++;
        return this->insertIntoPool(matrixName, indx, indy);
    }
}

/**
 * @brief Checks to see if a page exists in the pool
 *
 * @param pageName 
 * @return true 
 * @return false 
 */
bool BufferManager::inPool(string pageName)
{
    logger.log("BufferManager::inPool");
    for (auto page : this->pages)
    {
        if (pageName == page.pageName)
            return true;
    }
    return false;
}

/**
 * @brief If the page is present in the pool, then this function returns the
 * page. Note that this function will fail if the page is not present in the
 * pool.
 *
 * @param pageName 
 * @return Page 
 */
Page BufferManager::getFromPool(string pageName)
{
    logger.log("BufferManager::getFromPool");
    for (auto page : this->pages)
        if (pageName == page.pageName)
            return page;
}

/**
 * @brief Inserts page indicated by tableName and pageIndex into pool. If the
 * pool is full, the pool ejects the oldest inserted page from the pool and adds
 * the current page at the end. It naturally follows a queue data structure. 
 *
 * @param tableName 
 * @param pageIndex 
 * @return Page 
 */
Page BufferManager::insertIntoPool(string tableName, int pageIndex)
{
    logger.log("BufferManager::insertIntoPool");
    Page page(tableName, pageIndex);
    if (this->pages.size() >= BLOCK_COUNT)
        pages.pop_front();
    pages.push_back(page);
    return page;
}

/**
 * @brief delete all pages corresponding to this matrixname 
 *
 * @param matrixName 
 */
void BufferManager::deleteFromPool(string matrixName)
{
    logger.log("BufferManager::deleteFromPool");
    // remove those pages from pool (deque Page) for which pageName is same
    auto it = pages.begin();

    while(it != pages.end())
    {
        if(it->getMatrixName() == matrixName)
        {
            it = pages.erase(it);
        }
        else
        {
            it++;
        }
    }
}

void BufferManager::emptyPool()
{
    logger.log("BufferManager::EmptyPool");
    while(!pages.empty())
        pages.pop_back();
}

/**
 * @brief Inserts page indicated by  matrixName and {xind, yind} into pool. If the
 * pool is full, the pool ejects the oldest inserted page from the pool and adds
 * the current page at the end. It naturally follows a queue data structure. 
 *
 * @param matrixName 
 * @param xind
 * @param yind 
 * @return Page 
 */
Page BufferManager::insertIntoPool(string matrixName, int xind, int yind)
{
    logger.log("BufferManager::insertIntoPoolMatrix");
    Page page(matrixName, xind, yind);
    if (this->pages.size() >= BLOCK_COUNT)
        pages.pop_front();
    pages.push_back(page);
    return page;
}

/**
 * @brief The buffer manager is also responsible for writing pages. This is
 * called when new tables are created using assignment statements.
 *
 * @param tableName 
 * @param pageIndex 
 * @param rows 
 * @param rowCount 
 */
void BufferManager::writePage(string tableName, int pageIndex, vector<vector<int>> rows, int rowCount)
{
    logger.log("BufferManager::writePage");
    Page page(tableName, pageIndex, rows, rowCount);
    page.writePage();
}

/**
 * @brief The buffer manager is also responsible for writing pages. This is
 * called when new matrices are created using assignment/load statements.
 *
 * @param matrixName 
 * @param xind
 * @param yind
 * @param arr 
 */
void BufferManager::writeMatrixPage(string matrixName, int indx, int indy, vector<int> &arr)
{
    logger.log("BufferManager::writePage");
    Page page(matrixName, indx, indy, arr);
    page.writeMatrixPage();
}

/**
 * @brief Deletes file names fileName
 *
 * @param fileName 
 */
void BufferManager::deleteFile(string fileName)
{
    
    if (remove(fileName.c_str()))
        logger.log("BufferManager::deleteFile: Err");
        else logger.log("BufferManager::deleteFile: Success");
}

/**
 * @brief Overloaded function that calls deleteFile(fileName) by constructing
 * the fileName from the tableName and pageIndex.
 *
 * @param tableName 
 * @param pageIndex 
 */
void BufferManager::deleteFile(string tableName, int pageIndex)
{
    logger.log("BufferManager::deleteFile");
    string fileName = "../data/temp/"+tableName + "_Page" + to_string(pageIndex);
    this->deleteFile(fileName);
}

void BufferManager::printBlockAccessStat(){
    cout << "Number of blocks read: " << BLOCKS_READ << endl;
    cout << "Number of blocks written: " << BLOCKS_WRITTEN << endl;
    cout << "Number of blocks accessed: " << BLOCKS_READ + BLOCKS_WRITTEN << endl;
}